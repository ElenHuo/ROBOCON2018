#include "fs_pid.h" /* pid控制相关 */
#include "math.h" /* 数学函数 */


/*----------------------  初 始 化 例 子  -------------------------*/

///* 路径纠偏pid */
//pid_control_type path_correct_pid =
//{
//	.error_big_pid    = {.p = 0.15f, .i = 0, .d = 0}, /* 误差大/中/小三个区间的不同系数 */
//	.error_medium_pid = {.p = 0.12f, .i = 0, .d = 0},
//	.error_small_pid  = {.p = 0.08f, .i = 0, .d = 0},

//	.control_cycle         = GPS_UPDATE_CYCLE, /* 控制周期, 与微分和积分有关 */
//	.error_threshold_big   = 50, /* 大误差阈值 */
//	.error_threshold_small = 10, /* 小误差阈值 */
//	.error_dead_space 	   = 0, /* 死区误差 */

//	/* 每次限制取以下两个中最大的一个 */
//	.output_limit_abs         = 15, /* 输出限制 */
//	.output_limit_pointer_abs = &speed.actual_speed, /* 输出限制指针(被指向对象的值即为限制值) */
//};

/*-------------------------------------------------------------------*/


/*
* 函数: pid_control
* 描述: pid控制, 误差区间分类处理(算是模糊与pid结合)
* 参数: pid_struct, 对应误差类型的pid
*		error 误差值
*/
float pid_control(pid_control_type *pid_struct, float error)
{
	float output_value; /* 输出值 */
	float max_output; /* 最大输出限制 */
	pid_factor_type pid_factor; /* pid系数 */
	
	
	/*-----------------------------------------------------        pid 系 数 选 择        ----------------------------------------------------*/
	/* 误差很大 */
	if (fabsf(error) >= pid_struct->error_threshold_big)
	{
		pid_factor = pid_struct->error_big_pid; /* 使用大误差对应的pid参数 */
	}
	
	/* 误差中等 */
	else if (fabsf(error) >= pid_struct->error_threshold_small)
	{
		pid_factor = pid_struct->error_medium_pid; /* 使用中等误差对应的pid参数 */
	}
	
	/* 误差很小 */
	else if (fabsf(error) >= pid_struct->error_dead_space)
	{
		pid_factor = pid_struct->error_small_pid; /* 使用小误差对应的pid参数 */
	}
	
	/* 误差在死区内 */
	else
	{
		pid_factor.p = pid_factor.i = pid_factor.d = 0; /* 死区停止输出 */
	}
	
	/*----------------------------------------------------          误 差 记 录         -----------------------------------------------*/
	pid_struct->previous_error = pid_struct->current_error; /* 记录上次误差 */
	pid_struct->current_error = error; /* 记录当前误差 */
	
	/* 两次误差符号不同, 清空误差积分 */
	if ((pid_struct->previous_error > 0 && pid_struct->current_error < 0)
		|| (pid_struct->previous_error < 0 && pid_struct->current_error > 0))
	{
		pid_struct->integrate_error = 0;
	}
	
	/* 误差积分 = 梯形积分(对时间积分, 不受控制周期限制) */
	pid_struct->integrate_error += pid_struct->control_cycle 
				* (pid_struct->current_error + pid_struct->previous_error) / 2; 
	/* 误差微分 = 误差差值 / 控制周期 */
	pid_struct->differential_error = (pid_struct->current_error - pid_struct->previous_error) 
				/ pid_struct->control_cycle;
	/* 记录最大误差值 */
	if (fabsf(pid_struct->current_error) > pid_struct->max_error)
	{
		pid_struct->max_error = fabsf(pid_struct->current_error);
	}
	
	/*---------------------------------------------------    输 出 计 算 和 限 制     -------------------------------------------------*/
	output_value = pid_factor.p * pid_struct->current_error
				+ pid_factor.i * pid_struct->integrate_error
				+ pid_factor.d * pid_struct->differential_error;
	/* pid输出限制选择: 外部某变量(借助指针使用) 或 指定的某变量 */
//	if (pid_struct->output_limit_pointer_abs != NULL
//		&& fabsf(*pid_struct->output_limit_pointer_abs) > fabsf(pid_struct->output_limit_abs))
//	{
//		max_output = fabsf(*pid_struct->output_limit_pointer_abs);
//	}
//	/* 否则等于指定的变量 */
//	else 
//	{
//		max_output = fabsf(pid_struct->output_limit_abs);
//	}
	max_output = fabsf(pid_struct->output_limit_abs);
	/* 输出限制, 缩小比例, 符号不变 */
	if (fabsf(output_value) > fabsf(max_output))
	{
		output_value *= fabsf(max_output) / fabsf(output_value);  
	}
	
	return output_value;
}


