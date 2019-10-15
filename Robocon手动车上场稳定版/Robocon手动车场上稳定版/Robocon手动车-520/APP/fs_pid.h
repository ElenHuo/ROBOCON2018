#ifndef _PID_H_
#define _PID_H_

/*--------------------------------------------- �� �� �� -----------------------------------------------*/
#ifndef NULL
#define NULL (void *)0
#endif


/*---------------------------------------------  �� �� �� ��  ---------------------------------------------*/
/* pidϵ�� */
typedef struct
{
	float p; /* ����ϵ�� */
	float i; /* ����ϵ�� */
	float d; /* ΢��ϵ�� */
}pid_factor_type;

/* pid���Ͷ��� */
typedef struct
{
	pid_factor_type error_big_pid; /* ����/��/С��������Ĳ�ͬϵ�� */
	pid_factor_type error_medium_pid;
	pid_factor_type error_small_pid;

	float current_error; /* ��ǰ��� */
	float previous_error; /* �ϴ���� */
	
	float max_error; /* ������ */
	float integrate_error; /* ������ */
	float differential_error; /* ���΢�� */
	float control_cycle; /* �������� */
	float error_threshold_big; /* �������ֵ */
	float error_threshold_small; /* С�����ֵ */
	float error_dead_space; /* ������� */

	float output_limit_abs; /* ������� */
	float *output_limit_pointer_abs; /* �������ָ��(��ָ��Ķ���ֵ��Ϊ����ֵ) */
}pid_control_type;

/*----------------------  �� ʼ �� �� ��  -------------------------*/

///* pid */
//pid_control_type cm_speed_pid =
//{
//	.error_big_pid    = {.p = 0.8f, .i = 0, .d = 0}, /* ����/��/С��������Ĳ�ͬϵ�� */
//	.error_threshold_big   = 20, /* �������ֵ */
//	.error_medium_pid = {.p = 0.4f, .i = 0, .d = 0},
//	.error_threshold_small = 10, /* С�����ֵ */
//	.error_small_pid  = {.p = 0.1f, .i = 0, .d = 0},
//	.error_dead_space = 0,

//	.control_cycle         = 1, /* ��������, ��΢�ֺͻ����й� */

//	/* ÿ������ȡ��������������һ�� */
//	.output_limit_abs         = 500, /* ������� */
//	.output_limit_pointer_abs = NULL, /* �������ָ��(��ָ������ֵ��Ϊ����ֵ) */
//};

/*---------------------------------------------  �� �� �� ��  ---------------------------------------------*/
/* pid���� */
float pid_control(pid_control_type *pid_struct, float error);

#endif
