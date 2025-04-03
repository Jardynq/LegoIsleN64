#pragma once

// Items related to the Extra string of key-value pairs found in MxOb

struct Extra {
	enum ActionType {
		e_none = 0,
		e_opendisk,
		e_openram,
		e_close,
		e_start,
		e_stop,
		e_run,
		e_exit,
		e_enable,
		e_disable,
		e_notify,
		e_unknown,
	};
};

