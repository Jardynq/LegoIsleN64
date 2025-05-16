import bpy
import sys
import os

import sys

argv = sys.argv
argv = argv[argv.index("--") + 1:]

def main():
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.preferences.addon_enable(module="fast64")

    input_obj = argv[0]
    output_glb = argv[1]
    bpy.ops.wm.obj_import(filepath=input_obj)

    if bpy.ops.object.mode_set.poll():
        bpy.ops.object.mode_set(mode='OBJECT')

    name_map = {}
    for mat in bpy.data.materials:
        material_prepass(mat, name_map)

    bpy.context.scene.bsdf_conv_all = True
    bpy.context.scene.update_conv_all = True
    bpy.context.scene.rename_uv_maps = True
    bpy.ops.object.convert_bsdf()

    for mat in bpy.data.materials:
        material_postpass(mat, name_map)

    bpy.ops.export_scene.gltf(filepath=output_glb, export_format='GLB', export_extras=True, use_active_scene=True)
    bpy.ops.wm.quit_blender()




def texture_alpha_check(image):
    if image is None or image.channels < 4:
        return False
    if not image.has_data:
        image.pixels.load()

    alpha = (image.pixels[i] for i in range(3, len(image.pixels), 4))
    has_alpha = any(a >= 0.1 and a < 1 for a in alpha)
    has_cutout = any(a < 0.1 for a in alpha)
    return (has_alpha, has_cutout)

def material_prepass(mat, name_map):
    has_alpha = False
    has_texture = False
    has_tex_alpha = False
    has_tex_cutout = False
    if mat.use_nodes and 'Principled BSDF' in mat.node_tree.nodes:
        bsdf = mat.node_tree.nodes["Principled BSDF"]
        color = bsdf.inputs["Base Color"]
        alpha = bsdf.inputs["Alpha"]
        if len(color.links) > 0 and isinstance(color.links[0].from_node, bpy.types.ShaderNodeTexImage):
            has_texture = True
            tex = color.links[0].from_node.image
            (alpha, cutout) = texture_alpha_check(tex)
            if alpha:
                has_tex_alpha = True
            if cutout:
                has_tex_cutout = True
        elif len(alpha.links) == 0:
            if alpha.default_value < 1.0:
                has_alpha = True

    new_name = mat.name + "_f3d"
    if has_texture and has_tex_alpha:
        name_map[new_name] = 'Shaded Texture Transparent'
    elif has_texture and has_tex_cutout:
        name_map[new_name] = 'Shaded Texture Cutout'
    elif has_texture:
        name_map[new_name] = 'Shaded Texture'
    elif has_alpha:
        name_map[new_name] = 'Shaded Transparent'
    else:
        name_map[new_name] = 'Shaded Solid'

def set_combiner(comb, rgb, alpha):
    comb.A = rgb[0]
    comb.B = rgb[1]
    comb.C = rgb[2]
    comb.D = rgb[3]
    comb.A_alpha = alpha[0]
    comb.B_alpha = alpha[1]
    comb.C_alpha = alpha[2]
    comb.D_alpha = alpha[3]

def material_postpass(mat, name_map):
    is_f3d = 'is_f3d' in mat and 'f3d_mat' in mat and mat['is_f3d'] == True
    if not is_f3d:
        return

    preset = 'Shaded Solid'
    if mat.name in name_map:
        preset = name_map[mat.name]

    f3d = mat.f3d_mat
    rdp = f3d.rdp_settings

    rdp.set_rendermode = True
    f3d.set_combiner = True
    f3d.set_prim = False
    f3d.set_env = False
    f3d.set_blend = False

    rdp.g_cull_back = True
    rdp.g_cull_front = False
    rdp.g_mdsft_text_filt = 'G_TF_POINT' # 'G_TF_BILERP'
    rdp.g_fog = False
    rdp.g_tex_gen = False

    f3d.prim_color = f3d.default_light_color
    rdp.g_mdsft_cycletype = 'G_CYC_2CYCLE'

    # TODO, seems it doesn't export correctly?
    if preset == 'Shaded Solid':
        set_combiner(f3d.combiner1, ('PRIMITIVE', '0', 'SHADE', '0'), ('0', '0', '0', '1'))
        set_combiner(f3d.combiner1, ('COMBINED', '0', 'ENVIRONMENT', '0'), ('0', '0', '0', '1'))
        rdp.rendermode_preset_cycle_1 = 'G_RM_AA_ZB_OPA_SURF'
        rdp.rendermode_preset_cycle_2 = 'G_RM_AA_ZB_OPA_SURF2'
        f3d.set_prim = True
    elif preset == 'Shaded Transparent':
        set_combiner(f3d.combiner1, ('PRIMITIVE', '0', 'SHADE', '0'), ('0', '0', '0', '1'))
        set_combiner(f3d.combiner1, ('COMBINED', '0', 'ENVIRONMENT', '0'), ('0', '0', '0', 'SHADE'))
        rdp.rendermode_preset_cycle_1 = 'G_RM_AA_ZB_OPA_SURF'
        rdp.rendermode_preset_cycle_2 = 'G_RM_AA_ZB_XLU_SURF2'
        f3d.set_prim = True
    elif preset == 'Shaded Texture':
        set_combiner(f3d.combiner1, ('TEXEL0', '0', 'SHADE', '0'), ('0', '0', '0', '1'))
        set_combiner(f3d.combiner2, ('COMBINED', '0', 'ENVIRONMENT', '0'), ('0', '0', '0', '1'))
        rdp.rendermode_preset_cycle_1 = 'G_RM_AA_ZB_OPA_SURF'
        rdp.rendermode_preset_cycle_2 = 'G_RM_AA_ZB_OPA_SURF2'
    elif preset == 'Shaded Texture Transparent':
        set_combiner(f3d.combiner1, ('TEXEL0', '0', 'SHADE', '0'), ('0', '0', '0', '1'))
        set_combiner(f3d.combiner2, ('COMBINED', '0', 'ENVIRONMENT', '0'), ('TEXEL0', '0', 'SHADE', '0'))
        rdp.rendermode_preset_cycle_1 = 'G_RM_AA_ZB_OPA_SURF'
        rdp.rendermode_preset_cycle_2 = 'G_RM_AA_ZB_XLU_SURF2'
    elif preset == 'Shaded Texture Cutout':
        set_combiner(f3d.combiner1, ('TEXEL0', '0', 'SHADE', '0'), ('0', '0', '0', '1'))
        set_combiner(f3d.combiner2, ('COMBINED', '0', 'ENVIRONMENT', '0'), ('0', '0', '0', 'TEXEL0'))
        rdp.rendermode_preset_cycle_1 = 'G_RM_AA_ZB_OPA_SURF'
        rdp.rendermode_preset_cycle_2 = 'G_RM_AA_ZB_TEX_EDGE2'

    with bpy.context.temp_override(material=mat):
        bpy.ops.material.update_f3d_nodes()

if __name__ == "__main__":
    main()