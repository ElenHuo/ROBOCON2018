#include "fs_pid.h" /* pid������� */
#include "math.h" /* ��ѧ���� */


/*----------------------  �� ʼ �� �� ��  -------------------------*/

///* ·����ƫpid */
//pid_control_type path_correct_pid =
//{
//	.error_big_pid    = {.p = 0.15f, .i = 0, .d = 0}, /* ����/��/С��������Ĳ�ͬϵ�� */
//	.error_medium_pid = {.p = 0.12f, .i = 0, .d = 0},
//	.error_small_pid  = {.p = 0.08f, .i = 0, .d = 0},

//	.control_cycle         = GPS_UPDATE_CYCLE, /* ��������, ��΢�ֺͻ����й� */
//	.error_threshold_big   = 50, /* �������ֵ */
//	.error_threshold_small = 10, /* С�����ֵ */
//	.error_dead_space 	   = 0, /* ������� */

//	/* ÿ������ȡ��������������һ�� */
//	.output_limit_abs         = 15, /* ������� */
//	.output_limit_pointer_abs = &speed.actual_speed, /* �������ָ��(��ָ������ֵ��Ϊ����ֵ) */
//};

/*-------------------------------------------------------------------*/


/*
* ����: pid_control
* ����: pid����, ���������ദ��(����ģ����pid���)
* ����: pid_struct, ��Ӧ������͵�pid
*		error ���ֵ
*/
float pid_control(pid_control_type *pid_struct, float error)
{
	float output_value; /* ���ֵ */
	float max_output; /* ���������� */
	pid_factor_type pid_factor; /* pidϵ�� */
	
	
	/*-----------------------------------------------------        pid ϵ �� ѡ ��        ----------------------------------------------------*/
	/* ���ܴ� */
	if (fabsf(error) >= pid_struct->error_threshold_big)
	{
		pid_factor = pid_struct->error_big_pid; /* ʹ�ô�����Ӧ��pid���� */
	}
	
	/* ����е� */
	else if (fabsf(error) >= pid_struct->error_threshold_small)
	{
		pid_factor = pid_struct->error_medium_pid; /* ʹ���е�����Ӧ��pid���� */
	}
	
	/* ����С */
	else if (fabsf(error) >= pid_struct->error_dead_space)
	{
		pid_factor = pid_struct->error_small_pid; /* ʹ��С����Ӧ��pid���� */
	}
	
	/* ����������� */
	else
	{
		pid_factor.p = pid_factor.i = pid_factor.d = 0; /* ����ֹͣ��� */
	}
	
	/*----------------------------------------------------          �� �� �� ¼         -----------------------------------------------*/
	pid_struct->previous_error = pid_struct->current_error; /* ��¼�ϴ���� */
	pid_struct->current_error = error; /* ��¼��ǰ��� */
	
	/* ���������Ų�ͬ, ��������� */
	if ((pid_struct->previous_error > 0 && pid_struct->current_error < 0)
		|| (pid_struct->previous_error < 0 && pid_struct->current_error > 0))
	{
		pid_struct->integrate_error = 0;
	}
	
	/* ������ = ���λ���(��ʱ�����, ���ܿ�����������) */
	pid_struct->integrate_error += pid_struct->control_cycle 
				* (pid_struct->current_error + pid_struct->previous_error) / 2; 
	/* ���΢�� = ����ֵ / �������� */
	pid_struct->differential_error = (pid_struct->current_error - pid_struct->previous_error) 
				/ pid_struct->control_cycle;
	/* ��¼������ֵ */
	if (fabsf(pid_struct->current_error) > pid_struct->max_error)
	{
		pid_struct->max_error = fabsf(pid_struct->current_error);
	}
	
	/*---------------------------------------------------    �� �� �� �� �� �� ��     -------------------------------------------------*/
	output_value = pid_factor.p * pid_struct->current_error
				+ pid_factor.i * pid_struct->integrate_error
				+ pid_factor.d * pid_struct->differential_error;
	/* pid�������ѡ��: �ⲿĳ����(����ָ��ʹ��) �� ָ����ĳ���� */
//	if (pid_struct->output_limit_pointer_abs != NULL
//		&& fabsf(*pid_struct->output_limit_pointer_abs) > fabsf(pid_struct->output_limit_abs))
//	{
//		max_output = fabsf(*pid_struct->output_limit_pointer_abs);
//	}
//	/* �������ָ���ı��� */
//	else 
//	{
//		max_output = fabsf(pid_struct->output_limit_abs);
//	}
	max_output = fabsf(pid_struct->output_limit_abs);
	/* �������, ��С����, ���Ų��� */
	if (fabsf(output_value) > fabsf(max_output))
	{
		output_value *= fabsf(max_output) / fabsf(output_value);  
	}
	
	return output_value;
}


