#include <stdio.h>
#define SIZE 16 /* 表示させる盤面の要素数 SIZEを16と定義 */
#define SPACE 100 /* マス目を表示させるための値SPACEを100と定義 */
#define SPACE_CHAR "＋" /* 表示させるマス目SPACE_CHARを＋と定義 */
#define BLACK 40 /* 黒石の値BLACKを40と定義 */
#define BLACK_CHAR "●" /* 表示させる黒石BLACK_CHARを●と定義 */
#define WHITE 30 /* 白石の値WHITEを30と定義 */
#define WHITE_CHAR "○" /* 表示させる白石WHITE_CHARを○と定義 */

void initialization(void); /* 盤面を初期化するための関数 */
void expression(void); /* 盤面を表示させるための関数 */
void point_check(void); /* 座標入力とルール違反、禁じ手のチェックをする関数 */
void complete(void); /* 勝利判定の関数 */
void count(void); /* 同じ色が連続的に何個置かれているかを数える関数 */
int board[SIZE][SIZE],point_x,point_y,i,j,player=1,winner=5; /* 整数型配列 board[SIZE][SIZE](二次元配列),整数型 point_x(入力された行の値),整数型 point_y(入力された列の値), 整数型 i(行), 整数型 j(列), 整数型 player(プレイヤーの順番(初期値1)), 整数型 winner(勝利判定に使う値(初期値5)) */
int count_i,count_j,count_ru,count_lu; /* 整数型 count_i(横に連続した碁石のカウント), 整数型 count_j(縦に連続した碁石のカウント), 整数型 count_ru(右斜め上と右斜め下の連続した碁石のカウント), 整数型 count_lu(左斜め上と左斜め下のカウント) */
int count_judge1=100,count_judge2=100,count_judge3=100,count_judge4=100; /* 整数型 count_judge1(横の活三,活四判定(初期値100)), 整数型 count_judge2(縦の活三,活四判定(初期値100)), 整数型 count_judge3(右斜め上と右斜め下の活三,活四判定(初期値100)), 整数型 count_judge4(左斜め上と左斜め下の活三,活四判定(初期値100)) */
int kin_count_i,kin_count_j,kin_count_ru,kin_count_lu,kin_total1=0,kin_total2=0,kin_total3=0,kin_total4=0; /* 整数型 kin_count_i(禁じ手に使う連続した縦の碁石のカウント), 整数型 kin_count_j(禁じ手に使う連続した横の碁石のカウント), 整数型 kin_count_ru(禁じ手に使う連続した右斜め上と右斜め下の碁石のカウント), 整数型 kin_count_lu(禁じ手に使う連続した左斜め上と左斜め下の碁石のカウント), 整数型 kin_total1(禁じ手に使う変数(縦)), 整数型 kin_total2(禁じ手に使う変数(横)), 整数型 kin_total3(禁じ手に使う変数(右斜め上と右斜め下)), 整数型 kin_total4(禁じ手に使う変数(左斜め上と左斜め下)) */

int main(void){

	initialization(); /* initialization関数の呼び出し */

	while(1){ /* 無限ループ */
		expression(); /* expression関数の呼び出し */
		point_check(); /* check関数の呼び出し */
		complete(); /* complete関数の呼び出し */
		if(winner==0||winner==1||winner==2){ /* winnerが0か1か2のとき抜け出す。 */
			break;
		}
	}
	if(winner==0){ /* winnerが0の時 */
		printf("先手の勝ちです。\n"); /* 結果表示 */
	}
	else if(winner==1){ /* winnerが1の時 */
		printf("後手の勝ちです。\n"); /* 結果表示 */
	}
	else{ /* それ以外 */
		printf("終了します。\n"); /* 結果表示 */
	}
	return 0;
}

void initialization(void){
	for(i=1;i<SIZE;i++){ /* iループ */
		for(j=1;j<SIZE;j++){ /* jループ */
			board[i][j]=SPACE; /* SPACEを盤面に代入 */
		}
	}
	for(i=0;i<SIZE;i++){ /* iループ */
		for(j=0;j<SIZE;j++){ /* jループ */
			if(i==0){ /* iが0の場合 */
				board[i][j]=j; /* jの値を代入 */
			}
			else if(j==0&&i!=0){ /* jが0かつ、iが0じゃない場合 */
				board[i][j]=i; /* iの値を代入 */
			}
			else if(i==8&&j==8){ /* iが8かつ、jが8の場合 */
				board[i][j]=BLACK; /* BLACKの値を代入 */
			}
		}
	}
	return;
}

void expression(void){
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(i==0){
				printf("%02d", board[i][j]); /* 列番号表示 */
			}
			else if(j==0&&i!=0){
				printf("%02d",board[i][j]); /* 行番号表示 */
			}
		}
		for(j=1;j<SIZE;j++){
			if(board[i][j]==SPACE&&i!=0){ /* 盤面の位置を判定 */
				printf("%s",SPACE_CHAR); /* 盤面の位置に＋を表示 */
			}
		 	else if(board[i][j]==BLACK&&i!=0){ /* 盤面の位置を判定 */
				printf("%s",BLACK_CHAR); /* 盤面の位置に●を表示 */
			}
			else if(board[i][j]==WHITE&&i!=0){ /* 盤面の位置を判定 */
				printf("%s",WHITE_CHAR); /* 盤面の位置に○を表示 */
			}
		}
		printf("\n"); /* 改行 */
	}
	printf("\n"); /* 改行 */
	return;
}

void point_check(void){

	player++; /* playerをインクリメント */

	printf("座標をピリオド区切りで入力してください。\n"); /* プロンプト */
	if(player%2==0){ /* 後手の場合 */
		printf("後手の番です。\n"); /* 結果表示 */
	}
	else{ /* 先手の場合 */
		printf("先手の番です。\n");/* 結果表示 */
	}

		while(1){ /* 無限ループ */
		printf("(0.0)で終了\n座標 (行番号.列番号):"); /* プロンプト */
		scanf("%d.%d",&point_x,&point_y); /* 入力 */

		if(point_x==0&&point_y==0){ /* 0.0が入力された場合 */
			winner=2; /* winnerに2を代入 */
			break;
		}
		if(point_x<1||point_x>15||point_y<1||point_y>15){ /* 盤面以外の位置が指定された場合 */
			printf("ここには置けません。再入力して下さい。\n"); /* 再入力表示 */
			continue;
		}
		else if(player==2&&(point_y<7||point_y>9||point_x<7||point_x>9)){ /* 後手一手目が8.8の一回り外の位置に打たれなかった場合 */
			printf("ルール違反です。再入力して下さい。\n"); /* 再入力表示 */
			continue;
		}
		else if(board[point_x][point_y]==BLACK||board[point_x][point_y]==WHITE){ /* 指定した位置に碁石が置いてあるかどうか */
			printf("既に碁石が置かれています。再入力して下さい。\n"); /* 再入力表示 */
			continue;
		}
		else{ /* ルール違反がなかった場合 */
			if(player%2==1) /* 先手の場合 */
				board[point_x][point_y]=BLACK; /* board[point_x][point_y]にBLACKを代入 */
			if(player%2==0) /* 後手の場合 */
				board[point_x][point_y]=WHITE; /* board[point_x][point_y]にWHITEを代入 */
		}
		count(); /* 関数内関数呼び出し */
		if(player%2==1){ /* 先手の場合 */
			if(count_i>=5||count_j>=5||count_ru>=5||count_lu>=5){ /* 直線状に6つ以上同じ碁石が置かれている場合 */
				printf("長連になるため、再入力してください。\n"); /* 再入力表示 */
				board[point_x][point_y]=SPACE; /* board[point_x][point_y]にSPACEを代入 */
				continue;
			}
			if(count_judge1+count_judge2==3||count_judge2+count_judge3==5||count_judge3+count_judge4==7||count_judge4+count_judge1==5||count_judge1+count_judge3==4||count_judge2+count_judge4==6){ /* 活三、活四かどうか */
				if(kin_total1+kin_total2==4||kin_total2+kin_total3==4||kin_total3+kin_total4==4||kin_total4+kin_total1==4||kin_total3+kin_total1==4||kin_total2+kin_total4==4){ /* 三三かどうか */
					printf("三々になるため、再入力してください。\n"); /* 再入力表示 */
					board[point_x][point_y]=SPACE; /* board[point_x][point_y]にSPACEを代入 */
					continue;
				}

				if(kin_total2+kin_total3==6||kin_total2+kin_total3==6||kin_total3+kin_total4==6||kin_total4+kin_total1==6||kin_total3+kin_total1==6||kin_total2+kin_total4==6){ /* 四四かどうか */
					printf("四々になるため、再入力してください。\n"); /* 再入力表示 */
					board[point_x][point_y]=SPACE; /* board[point_x][point_y]にSPACEを代入 */
					continue;
				}
			}
		}
		break;
	}
	return;
}

void complete(void){

	count(); /* 関数内関数呼び出し */

	if(count_i==4||count_j==4||count_ru==4||count_lu==4){ /* 同じ碁石が5つ直線上にあるかどうか */
		if(player%2==1){ /* 先手の場合 */
			winner=0; /* winnerに0を代入 */
		}
		else{ /* 後手の場合 */
			winner=1; /* winnerに1を代入 */
		}
	}
	return; /* 戻り値なし */
}

void count(void){
	int k,l; /* 整数型 k(行) 整数型 l(列) */
	count_i=0; /* 0を代入 */
	count_j=0; /* 0を代入 */
	count_ru=0; /* 0を代入 */
	count_lu=0; /* 0を代入 */
	kin_count_i=0; /* 0を代入 */
	kin_count_j=0; /* 0を代入 */
	kin_count_ru=0; /* 0を代入 */
	kin_count_lu=0; /* 0を代入 */

	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k][l+1]){	/*右の碁石のカウント*/
		count_j++; /* 横に連続した碁石のカウント */
		l++; /* l列をインクリメント */
		if(board[k][l+1]==SPACE&&board[k][l-3]==SPACE){ /* 活三の条件式 */
			count_judge1=1; /* 活三、活四判定 */
		}
		if(board[k][l+1]==SPACE&&board[k][l-4]==SPACE){ /* 活四の条件式 */
			count_judge1=1; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k][l+2])&&(board[k][l+1]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_j++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k][l+2]==board[k][l+3]){ /*右の碁石のカウント*/
			kin_count_j++; /* 禁じ手に使うカウント(横)をインクリメント */
			l++; /* l列をインクリメント */
			if((board[k][l+3]==SPACE&&board[k][l-2]==SPACE)||(board[k][l+2]==SPACE&&board[k][l-3]==SPACE)){ /* 活三の条件式 */
				count_judge1=1; /* 活三、活四判定 */
			}
			if((board[k][l+4]==SPACE&&board[k][l-3]==SPACE)||(board[k][l+3]==SPACE&&board[k][l-4]==SPACE)){ /* 活四の条件式 */
				count_judge1=1; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k+1][l]){	/*下の碁石のカウント*/
		count_i++; /* 縦に連続した碁石のカウント */
		k++; /* k行をインクリメント */
		if(board[k+1][l]==SPACE&&board[k-3][l]==SPACE){ /* 活三の条件式 */
			count_judge2=2; /* 活三、活四判定 */
		}
		if(board[k+1][l]==SPACE&&board[k-4][l]==SPACE){ /* 活四の条件式 */
			count_judge2=2; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k+2][l])&&(board[k+1][l]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_i++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k+2][l]==board[k+3][l]){ /*下の碁石のカウント*/
			kin_count_i++; /* 禁じ手に使うカウント(縦)をインクリメント */
			k++; /* k行をインクリメント */
			if((board[k+3][l]==SPACE&&board[k-2][l]==SPACE)||(board[k+2][l]==SPACE&&board[k-3][l]==SPACE)){ /* 活三の条件式 */
				count_judge2=2; /* 活三、活四判定 */
			}
			if((board[k+4][l]==SPACE&&board[k-3][l]==SPACE)||(board[k+3][l]==SPACE&&board[k-4][l]==SPACE)){ /* 活四の条件式 */
				count_judge2=2; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k-1][l+1])	/*右上の碁石のカウント*/
	{
		count_ru++; /* 右斜め上の連続した碁石のカウント */
		k--; /* k行をデクリメント */
		l++; /* l列をインクリメント */
		if(board[k-1][l+1]==SPACE&&board[k+3][l-3]==SPACE){ /* 活三の条件式 */
			count_judge3=3; /* 活三、活四判定 */
		}
		if(board[k-1][l+1]==SPACE&&board[k+4][l-4]==SPACE){ /* 活四の条件式 */
			count_judge3=3; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k-2][l+2])&&(board[k-1][l+1]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_ru++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k-2][l+2]==board[k-3][l+3]){ /* 右上の碁石のカウント */
			kin_count_ru++; /* 禁じ手に使うカウント(右斜め上と右斜め下)をインクリメント */
			k--; /* k行をデクリメント */
			l++; /* l列をインクリメント */
			if((board[k-3][l+3]==SPACE&&board[k+2][l-2]==SPACE)||(board[k-2][l+2]==SPACE&&board[k+3][l-3]==SPACE)){ /* 活三の条件式 */
				count_judge3=3; /* 活三、活四判定 */
			}
			if((board[k-4][l+4]==SPACE&&board[k+3][l-3]==SPACE)||(board[k-3][l+3]==SPACE&&board[k+4][l-4]==SPACE)){ /* 活四の条件式 */
				count_judge3=3; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k-1][l-1]){	/*左上の碁石のカウント*/
		count_lu++; /* 左斜め上の連続した碁石のカウント */
		k--; /* k行をデクリメント */
		l--; /* l列をデクリメント */
		if(board[k-1][l-1]==SPACE&&board[k+3][l+3]==SPACE){ /* 活三の条件式 */
			count_judge4=4; /* 活三、活四判定 */
		}
		if(board[k-1][l-1]==SPACE&&board[k+4][l+4]==SPACE){ /* 活四の条件式 */
			count_judge4=4; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k+2][l+2])&&(board[k+1][l+1]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_lu++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k+3][l+3]==board[k+3][l+4]){ /*左上の碁石のカウント*/
			kin_count_lu++; /* 禁じ手に使うカウント(左斜め上と左斜め下)をインクリメント */
			k--; /* k行をデクリメント */
			l--; /* l列をデクリメント */
			if((board[k-3][l-3]==SPACE&&board[k+2][l+2]==SPACE)||(board[k-2][l-2]==SPACE&&board[k+3][l+3]==SPACE)){ /* 活三の条件式 */
				count_judge4=4; /* 活三、活四判定 */
			}
			if((board[k-4][l-4]==SPACE&&board[k+3][l+3]==SPACE)||(board[k-3][l-3]==SPACE&&board[k+4][l+4]==SPACE)){ /* 活四の条件式 */
				count_judge4=4; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k][l-1]){	/*左の碁石のカウント*/
		count_j++; /* 横に連続した碁石のカウント */
		l--; /* l列をデクリメント */
		if(board[k][l-1]==SPACE&&board[k][l+3]==SPACE){ /* 活三の条件式 */
			count_judge1=1; /* 活三、活四判定 */
		}
		if(board[k][l-1]==SPACE&&board[k][l+4]==SPACE){ /* 活四の条件式 */
			count_judge1=1; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k][l-2])&&(board[k][l-1]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_j++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k][l-2]==board[k][l-3]){ /*左の碁石のカウント*/
			kin_count_j++; /* 禁じ手に使うカウント(横)をインクリメント */
			l--; /* l列をデクリメント */
			if((board[k][l-3]==SPACE&&board[k][l+2]==SPACE)||(board[k][l-2]==SPACE&&board[k][l+3]==SPACE)){ /* 活三の条件式 */
				count_judge1=1; /* 活三、活四判定 */
			}
			if((board[k][l-4]==SPACE&&board[k][l+3]==SPACE)||(board[k][l-3]==SPACE&&board[k][l+4]==SPACE)){ /* 活四の条件式 */
				count_judge1=1; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k-1][l]){	/*上の碁石のカウント*/
		count_i++; /* 縦に連続した碁石のカウント */
		k--; /* k行をデクリメント */
		if(board[k-1][l]==SPACE&&board[k+3][l]==SPACE){ /* 活三の条件式 */
			count_judge2=2; /* 活三、活四判定 */
		}
		if(board[k-1][l]==SPACE&&board[k+4][l]==SPACE){ /* 活四の条件式 */
			count_judge2=2; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k-2][l])&&(board[k-1][l]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_i++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k-2][l]==board[k-3][l]){ /*上の碁石のカウント*/
			kin_count_i++; /* 禁じ手に使うカウント(縦)をインクリメント */
			k--; /* k行をデクリメント */
			if((board[k-3][l]==SPACE&&board[k+2][l]==SPACE)||(board[k-2][l]==SPACE&&board[k+3][l]==SPACE)){ /* 活三の条件式 */
				count_judge2=2; /* 活三、活四判定 */
			}
			if((board[k-4][l]==SPACE&&board[k+3][l]==SPACE)||(board[k-3][l]==SPACE&&board[k+4][l]==SPACE)){ /* 活四の条件式 */
				count_judge2=2; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k+1][l-1]){	/*左下の碁石のカウント*/
		count_ru++; /* 左斜め下の連続した碁石のカウント */
		k++; /* k行をインクリメント */
		l--; /* l列をデクリメント */
		if(board[k+1][l-1]==SPACE&&board[k-3][l+3]==SPACE){ /* 活三の条件式 */
			count_judge3=3; /* 活三、活四判定 */
		}
		if(board[k+1][l-1]==SPACE&&board[k-4][l+4]==SPACE){ /* 活四の条件式 */
			count_judge3=3; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k+2][l-2])&&(board[k+1][l-1]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_ru++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k+3][l-3]==board[k+4][l-4]){ /*左下の碁石のカウント*/
			kin_count_ru++; /* 禁じ手に使うカウント(右斜め上と右斜め下)をインクリメント */
			k++; /* k行をインクリメント */
			l--; /* l列をデクリメント */
			if((board[k+3][l-3]==SPACE&&board[k-2][l+2]==SPACE)||(board[k+2][l-2]==SPACE&&board[k-3][l+3]==SPACE)){ /* 活三の条件式 */
				count_judge3=3; /* 活三判定 */
			}
			if((board[k+4][l-4]==SPACE&&board[k-3][l+3]==SPACE)||(board[k+3][l-3]==SPACE&&board[k-4][l+4]==SPACE)){ /* 活四の条件式 */
				count_judge3=3; /* 活三、活四判定 */
			}
		}
	}
	k=point_x; /* 入力されたx座標の値point_xをkに代入 */
	l=point_y; /* 入力されたy座標の値point_yをlに代入 */
	while(board[k][l]==board[k+1][l+1]){	/*右下の碁石のカウント*/
		count_lu++; /* 右斜め下の連続した碁石のカウント */
		k++; /* k行をインクリメント */
		l++; /* l列をインクリメント */
		if(board[k+1][l+1]==SPACE&&board[k-3][l-3]==SPACE){ /* 活三の条件式 */
			count_judge4=4; /* 活三、活四判定 */
		}
		if(board[k+1][l+1]==SPACE&&board[k-4][l-4]==SPACE){ /* 活四の条件式 */
			count_judge4=4; /* 活三、活四判定 */
		}
	}
	if((board[k][l]==board[k+2][l+2])&&(board[k+1][l+1]==SPACE)){ /* 一個飛ばしの場合の条件 */
		kin_count_lu++; /* 禁じ手に使うカウントをインクリメント */
		while(board[k+2][l+2]==board[k+3][l+3]){ /*右下の碁石のカウント*/
			kin_count_lu++; /* 禁じ手に使うカウント(左斜め上と左斜め下)をインクリメント */
			k++; /* k行インクリメント */
			l++; /* l列インクリメント */
			if((board[k+3][l+3]==SPACE&&board[k-2][l-2]==SPACE)||(board[k+2][l+2]==SPACE&&board[k-3][l-3]==SPACE)){ /* 活三の条件式 */
				count_judge4=4; /* 活三、活四判定 */
			}
			if((board[k+4][l+4]==SPACE&&board[k-3][l-3]==SPACE)||(board[k+3][l+3]==SPACE&&board[k-4][l-4]==SPACE)){ /* 活四の条件式 */
				count_judge4=4; /* 活三、活四判定 */
			}
		}
	}
	kin_total1=count_i+kin_count_i; /* 禁じてに使うカウント(縦)の計算 */
	kin_total2=count_j+kin_count_j; /* 禁じ手に使うカウント(横)の計算 */
	kin_total3=count_ru+kin_count_ru; /* 禁じ手に使うカウント(右斜め上と右斜め下)の計算 */
	kin_total4=count_lu+kin_count_lu; /* 禁じ手に使うカウント(左斜め上と左斜め下)の計算 */

	return; /* 戻り値無し */
}
