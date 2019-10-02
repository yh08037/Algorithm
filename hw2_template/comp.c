#include <stdio.h>

//문자열을 입력받기 위해 main에 매개변수를 정해줌
int main(int argc, char** argv){
  FILE* fp1;
  FILE* fp2;
  int state1, state2;
  char a, b;

  //사용자가 입력을 잘못할 경우에 오류발생
  if (argc != 3){
      printf("[실행파일이름 텍스트파일이름 텍스트파일이름] 형식으로 입력하세요.\n");
      return 1;
  }
  //사용자가 입력한 이름의 텍스트 파일을
  //rt모드로 스트림 생성
  fp1 = fopen(argv[1], "rt");
  fp2 = fopen(argv[2], "rt");

  /* fopen함수는 오류발생시 NULL을 리턴하므로
  파일 개방 중 오류발생시 프로그램을 종료 */
  if (fp1 == NULL || fp2 == NULL) {
     printf("스트림 생성시 오류발생\n");
     return 1;
  }

  // 두개의 파일에 저장된 데이터를 비교함
  while (1){
    //두개의 파일 모두 끝에 도달하지 않을 경우
    if (feof(fp1) == 0 && feof(fp2) == 0){
      a = fgetc(fp1);
      b = fgetc(fp2);

      if (a != b){
        printf("두개의 파일은 일치하지 않습니다.\n");
        break;
      }
    }

    //하나의 파일만 끝에 도달할 경우
    else if (feof(fp1) != 0 && feof(fp2) == 0){
      printf("두개의 파일은 일치하지 않습니다.\n");
      break;
    }

    //하나의 파일만 끝에 도달할 경우
    else if (feof(fp1) == 0 && feof(fp2) != 0){
      printf("두개의 파일은 일치하지 않습니다.\n");
      break;
    }

    //두개의 파일 모두 끝에 도달한 경우.
    //(첫 번째 조건문에서 각 파일의 문자는 검사했기 때문에
    //두 파일이 동시에 feof에 의해 탈출하면 동일한 파일인 것)
    else{
      printf("두개의 파일은 일치합니다.\n");
      break;
    }
  }

  /* fclose함수는 종료시 오류가 발생하면
  0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
  안내후 프로그램을 종료 */
  state1 = fclose(fp1);
  state2 = fclose(fp2);

  if (state1 != 0 || state2 != 0){
    printf("스트림 제거시 오류발생\n");
    return 1;
  }

  return 0;
}
