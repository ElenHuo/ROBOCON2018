#ifndef _PID_H_
#define _PID_H_

/*--------------------------------------------- 宏 定 义 -----------------------------------------------*/
#ifndef NULL
#define NULL (void *)0
#endif


/*---------------------------------------------  类 型 定 义  ---------------------------------------------*/
/* pid系数 */
typedef struct
{
	float p; /* 比例系数 */
	float i; /* 积分系数 */
	float d; /* 微分系数 */
}pid_factor_type;

/* pid类型定义 */
typedef struct
{
	pid_factor_type error_big_pid; /* 误差大/中/小三个区间的不同系数 */
	pid_factor_type error_medium_pid;
	pid_factor_type error_small_pid;

	float current_error; /* 当前误差 */
	float previous_error; /* 上次误差 */
	
	float max_error; /* 最大误差 */
	float integrate_error; /* 误差积分 */
	float differential_error; /* 误差微分 */
	float control_cycle; /* 控制周期 */
	float error_threshold_big; /* 大误差阈值 */
	float error_threshold_small; /* 小误差阈值 */
	float error_dead_space; /* 死区误差 */

	float output_limit_abs; /* 输出限制 */
	float *output_limit_pointer_abs; /* 输出限制指针(被指向的对象值即为限制值) */
}pid_control_type;

/*----------------------  初 始 化 例 子  -------------------------*/

///* pid */
//pid_control_type cm_speed_pid =
//{
//	.error_big_pid    = {.p = 0.8f, .i = 0, .d = 0}, /* 误差大/中/小三个区间的不同系数 */
//	.error_threshold_big   = 20, /* 大误差阈值 */
//	.error_medium_pid = {.p = 0.4f, .i = 0, .d = 0},
//	.error_threshold_small = 10, /* 小误差阈值 */
//	.error_small_pid  = {.p = 0.1f, .i = 0, .d = 0},
//	.error_dead_space = 0,

//	.control_cycle         = 1, /* 控制周期, 与微分和积分有关 */

//	/* 每次限制取以下两个中最大的一个 */
//	.output_limit_abs         = 500, /* 输出限制 */
//	.output_limit_pointer_abs = NULL, /* 输出限制指针(被指向对象的值即为限制值) */
//};

/*---------------------------------------------  函 数 声 明  ---------------------------------------------*/
/* pid控制 */
float pid_control(pid_control_type *pid_struct, float error);

#endif
