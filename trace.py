import gdb
import re

trace_file = open("isle.trace", "w")
call_depth = 0

class ReturnTrace(gdb.FinishBreakpoint):
    def stop(self):
        global call_depth
        call_depth = max(0, call_depth - 1)
        return False

class TraceFunctionCall(gdb.Breakpoint):
    def __init__(self, spec):
        super().__init__(spec, internal=True)

    def stop(self):
        global call_depth
        frame = gdb.newest_frame()
        fn = frame.name()
        if fn is None:
            name = "<unknown>"
        else:
            parts = fn.split("::")
            if len(parts) >= 2 and parts[-1] == parts[-2]:
                name = "::" + parts[-1] # constructor
            elif len(parts) >= 2 and parts[-1].startswith("~") and parts[-1][1:] == parts[-2]:
                name =  "::-" + parts[-2] # destructor
            else:
                name = fn

        trace_file.write(f"{'  ' * call_depth}{name}\n")
        trace_file.flush()
        call_depth += 1
        try:
            ReturnTrace()
        except:
            pass
        return False


gdb.execute("set pagination off")
gdb.execute("set print frame-arguments all")
gdb.execute("set print pretty")
gdb.execute("set confirm off")

functions = gdb.execute("info functions", to_string=True)
for line in functions.splitlines():
    match = re.match(r'.*\b(\w+)\s*\(\)', line)
    if not match:
        continue
    name = match.group(1)

    try:
        sym = gdb.lookup_global_symbol(name)
        if sym is not None:
            TraceFunctionCall(name)
    except:
        continue

gdb.execute("run")
gdb.events.exited.connect(lambda _: trace_file.close())
