#include <stdio.h>
#define SIZE 16 /* �\��������Ֆʂ̗v�f�� SIZE��16�ƒ�` */
#define SPACE 100 /* �}�X�ڂ�\�������邽�߂̒lSPACE��100�ƒ�` */
#define SPACE_CHAR "�{" /* �\��������}�X��SPACE_CHAR���{�ƒ�` */
#define BLACK 40 /* ���΂̒lBLACK��40�ƒ�` */
#define BLACK_CHAR "��" /* �\�������鍕��BLACK_CHAR�����ƒ�` */
#define WHITE 30 /* ���΂̒lWHITE��30�ƒ�` */
#define WHITE_CHAR "��" /* �\�������锒��WHITE_CHAR�����ƒ�` */

void initialization(void); /* �Ֆʂ����������邽�߂̊֐� */
void expression(void); /* �Ֆʂ�\�������邽�߂̊֐� */
void point_check(void); /* ���W���͂ƃ��[���ᔽ�A�ւ���̃`�F�b�N������֐� */
void complete(void); /* ��������̊֐� */
void count(void); /* �����F���A���I�ɉ��u����Ă��邩�𐔂���֐� */
int board[SIZE][SIZE],point_x,point_y,i,j,player=1,winner=5; /* �����^�z�� board[SIZE][SIZE](�񎟌��z��),�����^ point_x(���͂��ꂽ�s�̒l),�����^ point_y(���͂��ꂽ��̒l), �����^ i(�s), �����^ j(��), �����^ player(�v���C���[�̏���(�����l1)), �����^ winner(��������Ɏg���l(�����l5)) */
int count_i,count_j,count_ru,count_lu; /* �����^ count_i(���ɘA��������΂̃J�E���g), �����^ count_j(�c�ɘA��������΂̃J�E���g), �����^ count_ru(�E�΂ߏ�ƉE�΂߉��̘A��������΂̃J�E���g), �����^ count_lu(���΂ߏ�ƍ��΂߉��̃J�E���g) */
int count_judge1=100,count_judge2=100,count_judge3=100,count_judge4=100; /* �����^ count_judge1(���̊��O,���l����(�����l100)), �����^ count_judge2(�c�̊��O,���l����(�����l100)), �����^ count_judge3(�E�΂ߏ�ƉE�΂߉��̊��O,���l����(�����l100)), �����^ count_judge4(���΂ߏ�ƍ��΂߉��̊��O,���l����(�����l100)) */
int kin_count_i,kin_count_j,kin_count_ru,kin_count_lu,kin_total1=0,kin_total2=0,kin_total3=0,kin_total4=0; /* �����^ kin_count_i(�ւ���Ɏg���A�������c�̌�΂̃J�E���g), �����^ kin_count_j(�ւ���Ɏg���A���������̌�΂̃J�E���g), �����^ kin_count_ru(�ւ���Ɏg���A�������E�΂ߏ�ƉE�΂߉��̌�΂̃J�E���g), �����^ kin_count_lu(�ւ���Ɏg���A���������΂ߏ�ƍ��΂߉��̌�΂̃J�E���g), �����^ kin_total1(�ւ���Ɏg���ϐ�(�c)), �����^ kin_total2(�ւ���Ɏg���ϐ�(��)), �����^ kin_total3(�ւ���Ɏg���ϐ�(�E�΂ߏ�ƉE�΂߉�)), �����^ kin_total4(�ւ���Ɏg���ϐ�(���΂ߏ�ƍ��΂߉�)) */

int main(void){

	initialization(); /* initialization�֐��̌Ăяo�� */

	while(1){ /* �������[�v */
		expression(); /* expression�֐��̌Ăяo�� */
		point_check(); /* check�֐��̌Ăяo�� */
		complete(); /* complete�֐��̌Ăяo�� */
		if(winner==0||winner==1||winner==2){ /* winner��0��1��2�̂Ƃ������o���B */
			break;
		}
	}
	if(winner==0){ /* winner��0�̎� */
		printf("���̏����ł��B\n"); /* ���ʕ\�� */
	}
	else if(winner==1){ /* winner��1�̎� */
		printf("���̏����ł��B\n"); /* ���ʕ\�� */
	}
	else{ /* ����ȊO */
		printf("�I�����܂��B\n"); /* ���ʕ\�� */
	}
	return 0;
}

/*
�֐��� initialization
�֐��̖��� �Ֆʂ�����������v���O����
���� �Ȃ�
�߂�l �Ȃ�
�S���� ���� ����(2016�N1��7���쐬)
 */
void initialization(void){
	for(i=1;i<SIZE;i++){ /* i���[�v */
		for(j=1;j<SIZE;j++){ /* j���[�v */
			board[i][j]=SPACE; /* SPACE��Ֆʂɑ�� */
		}
	}
	for(i=0;i<SIZE;i++){ /* i���[�v */
		for(j=0;j<SIZE;j++){ /* j���[�v */
			if(i==0){ /* i��0�̏ꍇ */
				board[i][j]=j; /* j�̒l���� */
			}
			else if(j==0&&i!=0){ /* j��0���Ai��0����Ȃ��ꍇ */
				board[i][j]=i; /* i�̒l���� */
			}
			else if(i==8&&j==8){ /* i��8���Aj��8�̏ꍇ */
				board[i][j]=BLACK; /* BLACK�̒l���� */
			}
		}
	}
	return;
}

/*
�֐��� expression
�֐��̖��� �Ֆʕ\��(��ԍ�,�s�ԍ��܂�)
���� �Ȃ�
�߂�l �Ȃ�
�S���� ��������(2016�N1��7���쐬)
*/
void expression(void){
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(i==0){
				printf("%02d", board[i][j]); /* ��ԍ��\�� */
			}
			else if(j==0&&i!=0){
				printf("%02d",board[i][j]); /* �s�ԍ��\�� */
			}
		}
		for(j=1;j<SIZE;j++){
			if(board[i][j]==SPACE&&i!=0){ /* �Ֆʂ̈ʒu�𔻒� */
				printf("%s",SPACE_CHAR); /* �Ֆʂ̈ʒu�Ɂ{��\�� */
			}
		 	else if(board[i][j]==BLACK&&i!=0){ /* �Ֆʂ̈ʒu�𔻒� */
				printf("%s",BLACK_CHAR); /* �Ֆʂ̈ʒu�Ɂ���\�� */
			}
			else if(board[i][j]==WHITE&&i!=0){ /* �Ֆʂ̈ʒu�𔻒� */
				printf("%s",WHITE_CHAR); /* �Ֆʂ̈ʒu�Ɂ���\�� */
			}
		}
		printf("\n"); /* ���s */
	}
	printf("\n"); /* ���s */
	return;
}

/*
�֐��� check
�֐��̖��� ���͂ƈᔽ�A�r���I���̔�����s��
���� �Ȃ�
�߂�l �Ȃ�
�S���� ���� �O��(2016�N1��18���쐬)
 */
void point_check(void){

	player++; /* player���C���N�������g */

	printf("���W���s���I�h��؂�œ��͂��Ă��������B\n"); /* �v�����v�g */
	if(player%2==0){ /* ���̏ꍇ */
		printf("���̔Ԃł��B\n"); /* ���ʕ\�� */
	}
	else{ /* ���̏ꍇ */
		printf("���̔Ԃł��B\n");/* ���ʕ\�� */
	}

		while(1){ /* �������[�v */
		printf("(0.0)�ŏI��\n���W (�s�ԍ�.��ԍ�):"); /* �v�����v�g */
		scanf("%d.%d",&point_x,&point_y); /* ���� */

		if(point_x==0&&point_y==0){ /* 0.0�����͂��ꂽ�ꍇ */
			winner=2; /* winner��2���� */
			break;
		}
		if(point_x<1||point_x>15||point_y<1||point_y>15){ /* �ՖʈȊO�̈ʒu���w�肳�ꂽ�ꍇ */
			printf("�����ɂ͒u���܂���B�ē��͂��ĉ������B\n"); /* �ē��͕\�� */
			continue;
		}
		else if(player==2&&(point_y<7||point_y>9||point_x<7||point_x>9)){ /* �����ڂ�8.8�̈���O�̈ʒu�ɑł���Ȃ������ꍇ */
			printf("���[���ᔽ�ł��B�ē��͂��ĉ������B\n"); /* �ē��͕\�� */
			continue;
		}
		else if(board[point_x][point_y]==BLACK||board[point_x][point_y]==WHITE){ /* �w�肵���ʒu�Ɍ�΂��u���Ă��邩�ǂ��� */
			printf("���Ɍ�΂��u����Ă��܂��B�ē��͂��ĉ������B\n"); /* �ē��͕\�� */
			continue;
		}
		else{ /* ���[���ᔽ���Ȃ������ꍇ */
			if(player%2==1) /* ���̏ꍇ */
				board[point_x][point_y]=BLACK; /* board[point_x][point_y]��BLACK���� */
			if(player%2==0) /* ���̏ꍇ */
				board[point_x][point_y]=WHITE; /* board[point_x][point_y]��WHITE���� */
		}
		count(); /* �֐����֐��Ăяo�� */
		if(player%2==1){ /* ���̏ꍇ */
			if(count_i>=5||count_j>=5||count_ru>=5||count_lu>=5){ /* �������6�ȏ㓯����΂��u����Ă���ꍇ */
				printf("���A�ɂȂ邽�߁A�ē��͂��Ă��������B\n"); /* �ē��͕\�� */
				board[point_x][point_y]=SPACE; /* board[point_x][point_y]��SPACE���� */
				continue;
			}
			if(count_judge1+count_judge2==3||count_judge2+count_judge3==5||count_judge3+count_judge4==7||count_judge4+count_judge1==5||count_judge1+count_judge3==4||count_judge2+count_judge4==6){ /* ���O�A���l���ǂ��� */
				if(kin_total1+kin_total2==4||kin_total2+kin_total3==4||kin_total3+kin_total4==4||kin_total4+kin_total1==4||kin_total3+kin_total1==4||kin_total2+kin_total4==4){ /* �O�O���ǂ��� */
					printf("�O�X�ɂȂ邽�߁A�ē��͂��Ă��������B\n"); /* �ē��͕\�� */
					board[point_x][point_y]=SPACE; /* board[point_x][point_y]��SPACE���� */
					continue;
				}

				if(kin_total2+kin_total3==6||kin_total2+kin_total3==6||kin_total3+kin_total4==6||kin_total4+kin_total1==6||kin_total3+kin_total1==6||kin_total2+kin_total4==6){ /* �l�l���ǂ��� */
					printf("�l�X�ɂȂ邽�߁A�ē��͂��Ă��������B\n"); /* �ē��͕\�� */
					board[point_x][point_y]=SPACE; /* board[point_x][point_y]��SPACE���� */
					continue;
				}
			}
		}
		break;
	}
	return;
}

/*
�֐��� complete
�֐��̖��� ���i���������
���� �Ȃ�
�߂�l �Ȃ�
�S���� ���� ����(2016�N1��7���쐬)
 */
void complete(void){

	count(); /* �֐����֐��Ăяo�� */

	if(count_i==4||count_j==4||count_ru==4||count_lu==4){ /* ������΂�5������ɂ��邩�ǂ��� */
		if(player%2==1){ /* ���̏ꍇ */
			winner=0; /* winner��0���� */
		}
		else{ /* ���̏ꍇ */
			winner=1; /* winner��1���� */
		}
	}
	return; /* �߂�l�Ȃ� */
}

/*
�֐��� count
�֐��̖��� ���i����Ƌւ���Ɏg���l���J�E���g����
���� �Ȃ�
�߂�l �Ȃ�
�S���� ���� �O��(2016�N1��18���쐬)
 */
void count(void){
	int k,l; /* �����^ k(�s) �����^ l(��) */
	count_i=0; /* 0���� */
	count_j=0; /* 0���� */
	count_ru=0; /* 0���� */
	count_lu=0; /* 0���� */
	kin_count_i=0; /* 0���� */
	kin_count_j=0; /* 0���� */
	kin_count_ru=0; /* 0���� */
	kin_count_lu=0; /* 0���� */

	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k][l+1]){	/*�E�̌�΂̃J�E���g*/
		count_j++; /* ���ɘA��������΂̃J�E���g */
		l++; /* l����C���N�������g */
		if(board[k][l+1]==SPACE&&board[k][l-3]==SPACE){ /* ���O�̏����� */
			count_judge1=1; /* ���O�A���l���� */
		}
		if(board[k][l+1]==SPACE&&board[k][l-4]==SPACE){ /* ���l�̏����� */
			count_judge1=1; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k][l+2])&&(board[k][l+1]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_j++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k][l+2]==board[k][l+3]){ /*�E�̌�΂̃J�E���g*/
			kin_count_j++; /* �ւ���Ɏg���J�E���g(��)���C���N�������g */
			l++; /* l����C���N�������g */
			if((board[k][l+3]==SPACE&&board[k][l-2]==SPACE)||(board[k][l+2]==SPACE&&board[k][l-3]==SPACE)){ /* ���O�̏����� */
				count_judge1=1; /* ���O�A���l���� */
			}
			if((board[k][l+4]==SPACE&&board[k][l-3]==SPACE)||(board[k][l+3]==SPACE&&board[k][l-4]==SPACE)){ /* ���l�̏����� */
				count_judge1=1; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k+1][l]){	/*���̌�΂̃J�E���g*/
		count_i++; /* �c�ɘA��������΂̃J�E���g */
		k++; /* k�s���C���N�������g */
		if(board[k+1][l]==SPACE&&board[k-3][l]==SPACE){ /* ���O�̏����� */
			count_judge2=2; /* ���O�A���l���� */
		}
		if(board[k+1][l]==SPACE&&board[k-4][l]==SPACE){ /* ���l�̏����� */
			count_judge2=2; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k+2][l])&&(board[k+1][l]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_i++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k+2][l]==board[k+3][l]){ /*���̌�΂̃J�E���g*/
			kin_count_i++; /* �ւ���Ɏg���J�E���g(�c)���C���N�������g */
			k++; /* k�s���C���N�������g */
			if((board[k+3][l]==SPACE&&board[k-2][l]==SPACE)||(board[k+2][l]==SPACE&&board[k-3][l]==SPACE)){ /* ���O�̏����� */
				count_judge2=2; /* ���O�A���l���� */
			}
			if((board[k+4][l]==SPACE&&board[k-3][l]==SPACE)||(board[k+3][l]==SPACE&&board[k-4][l]==SPACE)){ /* ���l�̏����� */
				count_judge2=2; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k-1][l+1])	/*�E��̌�΂̃J�E���g*/
	{
		count_ru++; /* �E�΂ߏ�̘A��������΂̃J�E���g */
		k--; /* k�s���f�N�������g */
		l++; /* l����C���N�������g */
		if(board[k-1][l+1]==SPACE&&board[k+3][l-3]==SPACE){ /* ���O�̏����� */
			count_judge3=3; /* ���O�A���l���� */
		}
		if(board[k-1][l+1]==SPACE&&board[k+4][l-4]==SPACE){ /* ���l�̏����� */
			count_judge3=3; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k-2][l+2])&&(board[k-1][l+1]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_ru++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k-2][l+2]==board[k-3][l+3]){ /* �E��̌�΂̃J�E���g */
			kin_count_ru++; /* �ւ���Ɏg���J�E���g(�E�΂ߏ�ƉE�΂߉�)���C���N�������g */
			k--; /* k�s���f�N�������g */
			l++; /* l����C���N�������g */
			if((board[k-3][l+3]==SPACE&&board[k+2][l-2]==SPACE)||(board[k-2][l+2]==SPACE&&board[k+3][l-3]==SPACE)){ /* ���O�̏����� */
				count_judge3=3; /* ���O�A���l���� */
			}
			if((board[k-4][l+4]==SPACE&&board[k+3][l-3]==SPACE)||(board[k-3][l+3]==SPACE&&board[k+4][l-4]==SPACE)){ /* ���l�̏����� */
				count_judge3=3; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k-1][l-1]){	/*����̌�΂̃J�E���g*/
		count_lu++; /* ���΂ߏ�̘A��������΂̃J�E���g */
		k--; /* k�s���f�N�������g */
		l--; /* l����f�N�������g */
		if(board[k-1][l-1]==SPACE&&board[k+3][l+3]==SPACE){ /* ���O�̏����� */
			count_judge4=4; /* ���O�A���l���� */
		}
		if(board[k-1][l-1]==SPACE&&board[k+4][l+4]==SPACE){ /* ���l�̏����� */
			count_judge4=4; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k+2][l+2])&&(board[k+1][l+1]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_lu++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k+3][l+3]==board[k+3][l+4]){ /*����̌�΂̃J�E���g*/
			kin_count_lu++; /* �ւ���Ɏg���J�E���g(���΂ߏ�ƍ��΂߉�)���C���N�������g */
			k--; /* k�s���f�N�������g */
			l--; /* l����f�N�������g */
			if((board[k-3][l-3]==SPACE&&board[k+2][l+2]==SPACE)||(board[k-2][l-2]==SPACE&&board[k+3][l+3]==SPACE)){ /* ���O�̏����� */
				count_judge4=4; /* ���O�A���l���� */
			}
			if((board[k-4][l-4]==SPACE&&board[k+3][l+3]==SPACE)||(board[k-3][l-3]==SPACE&&board[k+4][l+4]==SPACE)){ /* ���l�̏����� */
				count_judge4=4; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k][l-1]){	/*���̌�΂̃J�E���g*/
		count_j++; /* ���ɘA��������΂̃J�E���g */
		l--; /* l����f�N�������g */
		if(board[k][l-1]==SPACE&&board[k][l+3]==SPACE){ /* ���O�̏����� */
			count_judge1=1; /* ���O�A���l���� */
		}
		if(board[k][l-1]==SPACE&&board[k][l+4]==SPACE){ /* ���l�̏����� */
			count_judge1=1; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k][l-2])&&(board[k][l-1]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_j++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k][l-2]==board[k][l-3]){ /*���̌�΂̃J�E���g*/
			kin_count_j++; /* �ւ���Ɏg���J�E���g(��)���C���N�������g */
			l--; /* l����f�N�������g */
			if((board[k][l-3]==SPACE&&board[k][l+2]==SPACE)||(board[k][l-2]==SPACE&&board[k][l+3]==SPACE)){ /* ���O�̏����� */
				count_judge1=1; /* ���O�A���l���� */
			}
			if((board[k][l-4]==SPACE&&board[k][l+3]==SPACE)||(board[k][l-3]==SPACE&&board[k][l+4]==SPACE)){ /* ���l�̏����� */
				count_judge1=1; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k-1][l]){	/*��̌�΂̃J�E���g*/
		count_i++; /* �c�ɘA��������΂̃J�E���g */
		k--; /* k�s���f�N�������g */
		if(board[k-1][l]==SPACE&&board[k+3][l]==SPACE){ /* ���O�̏����� */
			count_judge2=2; /* ���O�A���l���� */
		}
		if(board[k-1][l]==SPACE&&board[k+4][l]==SPACE){ /* ���l�̏����� */
			count_judge2=2; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k-2][l])&&(board[k-1][l]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_i++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k-2][l]==board[k-3][l]){ /*��̌�΂̃J�E���g*/
			kin_count_i++; /* �ւ���Ɏg���J�E���g(�c)���C���N�������g */
			k--; /* k�s���f�N�������g */
			if((board[k-3][l]==SPACE&&board[k+2][l]==SPACE)||(board[k-2][l]==SPACE&&board[k+3][l]==SPACE)){ /* ���O�̏����� */
				count_judge2=2; /* ���O�A���l���� */
			}
			if((board[k-4][l]==SPACE&&board[k+3][l]==SPACE)||(board[k-3][l]==SPACE&&board[k+4][l]==SPACE)){ /* ���l�̏����� */
				count_judge2=2; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k+1][l-1]){	/*�����̌�΂̃J�E���g*/
		count_ru++; /* ���΂߉��̘A��������΂̃J�E���g */
		k++; /* k�s���C���N�������g */
		l--; /* l����f�N�������g */
		if(board[k+1][l-1]==SPACE&&board[k-3][l+3]==SPACE){ /* ���O�̏����� */
			count_judge3=3; /* ���O�A���l���� */
		}
		if(board[k+1][l-1]==SPACE&&board[k-4][l+4]==SPACE){ /* ���l�̏����� */
			count_judge3=3; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k+2][l-2])&&(board[k+1][l-1]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_ru++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k+3][l-3]==board[k+4][l-4]){ /*�����̌�΂̃J�E���g*/
			kin_count_ru++; /* �ւ���Ɏg���J�E���g(�E�΂ߏ�ƉE�΂߉�)���C���N�������g */
			k++; /* k�s���C���N�������g */
			l--; /* l����f�N�������g */
			if((board[k+3][l-3]==SPACE&&board[k-2][l+2]==SPACE)||(board[k+2][l-2]==SPACE&&board[k-3][l+3]==SPACE)){ /* ���O�̏����� */
				count_judge3=3; /* ���O���� */
			}
			if((board[k+4][l-4]==SPACE&&board[k-3][l+3]==SPACE)||(board[k+3][l-3]==SPACE&&board[k-4][l+4]==SPACE)){ /* ���l�̏����� */
				count_judge3=3; /* ���O�A���l���� */
			}
		}
	}
	k=point_x; /* ���͂��ꂽx���W�̒lpoint_x��k�ɑ�� */
	l=point_y; /* ���͂��ꂽy���W�̒lpoint_y��l�ɑ�� */
	while(board[k][l]==board[k+1][l+1]){	/*�E���̌�΂̃J�E���g*/
		count_lu++; /* �E�΂߉��̘A��������΂̃J�E���g */
		k++; /* k�s���C���N�������g */
		l++; /* l����C���N�������g */
		if(board[k+1][l+1]==SPACE&&board[k-3][l-3]==SPACE){ /* ���O�̏����� */
			count_judge4=4; /* ���O�A���l���� */
		}
		if(board[k+1][l+1]==SPACE&&board[k-4][l-4]==SPACE){ /* ���l�̏����� */
			count_judge4=4; /* ���O�A���l���� */
		}
	}
	if((board[k][l]==board[k+2][l+2])&&(board[k+1][l+1]==SPACE)){ /* ���΂��̏ꍇ�̏��� */
		kin_count_lu++; /* �ւ���Ɏg���J�E���g���C���N�������g */
		while(board[k+2][l+2]==board[k+3][l+3]){ /*�E���̌�΂̃J�E���g*/
			kin_count_lu++; /* �ւ���Ɏg���J�E���g(���΂ߏ�ƍ��΂߉�)���C���N�������g */
			k++; /* k�s�C���N�������g */
			l++; /* l��C���N�������g */
			if((board[k+3][l+3]==SPACE&&board[k-2][l-2]==SPACE)||(board[k+2][l+2]==SPACE&&board[k-3][l-3]==SPACE)){ /* ���O�̏����� */
				count_judge4=4; /* ���O�A���l���� */
			}
			if((board[k+4][l+4]==SPACE&&board[k-3][l-3]==SPACE)||(board[k+3][l+3]==SPACE&&board[k-4][l-4]==SPACE)){ /* ���l�̏����� */
				count_judge4=4; /* ���O�A���l���� */
			}
		}
	}
	kin_total1=count_i+kin_count_i; /* �ւ��ĂɎg���J�E���g(�c)�̌v�Z */
	kin_total2=count_j+kin_count_j; /* �ւ���Ɏg���J�E���g(��)�̌v�Z */
	kin_total3=count_ru+kin_count_ru; /* �ւ���Ɏg���J�E���g(�E�΂ߏ�ƉE�΂߉�)�̌v�Z */
	kin_total4=count_lu+kin_count_lu; /* �ւ���Ɏg���J�E���g(���΂ߏ�ƍ��΂߉�)�̌v�Z */

	return; /* �߂�l���� */
}
