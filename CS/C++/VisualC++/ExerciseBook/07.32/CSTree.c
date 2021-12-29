/*===================================
 * ���Ķ�������������-�ֵܣ��ṹ�洢��ʾ
 ====================================*/

#include "CSTree.h"

int count = 0;

/*
 * ��ʼ��
 *
 * ���������
 */
Status InitTree(CSTree* T) {
    if(T == NULL) {
        return ERROR;
    }
    
    *T = NULL;
    
    return OK;
}

/*
 * �п�
 *
 * �ж����Ƿ�Ϊ������
 */
Status TreeEmpty(CSTree T) {
    return T == NULL ? TRUE : FALSE;
}


/*�������������������������������������������� ͼ�λ���� ��������������������������������������������*/

// ��ͼ�λ���ʽ�����ǰ�ṹ
void PrintTree(CSTree T) {
    
    // ���������������������
    if(TreeEmpty(T)) {
        printf("\n");
        return;
    }
    
    Print(T, 0);
    
    printf("\n");
}

// ͼ�λ������ǰ�ṹ�ڲ�ʵ��
static void Print(CSTree T, int row) {
    int k;
    
    if(T == NULL) {
        return;
    }
    
    if(row==0) {
        printf("\n�� %d ����...\n", ++count);
    }
    
    // ���ʵ�ǰ���
    printf("%c ", T->data);
    
    Print(T->firstchild, row + 1);
    
    if(T->nextsibling != NULL) {
        printf("\n");
        
        for(k = 0; k < row; k++) {
            printf(". ");
        }
        
        Print(T->nextsibling, row);
    }
}