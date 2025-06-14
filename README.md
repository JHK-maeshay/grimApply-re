MFC GUI 구현
---
### How to Execute

루트폴더의 circleMaker.exe 를 실행하세요.

Visual C++ 2015 Redistributable (x64) 이상 버전이 설치되어있어야 합니다.

설치되지 않은 경우 dll 오류가 발생합니다.

### Preview

+ click to play

[![Video Label](http://img.youtube.com/vi/RDS-unQjt04/0.jpg)](https://youtu.be/RDS-unQjt04)

+ preview images

![Image](https://github.com/user-attachments/assets/c72c8904-8458-468d-a766-be5069485d52)

![Image](https://github.com/user-attachments/assets/46fc0517-209c-48b9-b486-23eec98570db)

### 다음 조건을 만족하는 MFC 인터페이스를 구현

- 세 번째 클릭 이후에 클릭 지점 3개를 모두 지나가는 정원 1개를 그립니다.
- 클릭 지점 원을 그릴 때의 반지름 크기는 사용자로부터 입력 받습니다.
- 각 클릭 지점 원의 중심 좌표를 UI에 표시합니다.
- 네 번째 클릭부터는 클릭 지점 원을 그리지 않습니다.
- 세 클릭 지점을 지나가는 정원의 내부는 채워지지 않아야 하며, 가장자리 두께는 사용자로부터 입력 받습니다.
- 클릭 지점 3개 중 하나를 클릭하고 드래그 했을 때 정원을 다시 그립니다.
- 이 때, 마우스 커서 좌표가 바뀌는 동안 즉, 마우스 드래그 상태가 끝날 때 까지 정원이 계속해서 이동하며 그려져야 합니다.
- [초기화] 버튼을 누르면 그려졌던 모든 내용들을 삭제하고 처음부터 입력 받을 수 있는 상태가 되어야 합니다.
- 정원이 그려진 상태에서 [랜덤 이동] 버튼을 누르면 3개의 클릭 지점 원 모두를 랜덤한 위치로 이동시킵니다.
- 이 때, 정원 또한 마찬가지로 다시 그려져야 합니다.
- 랜덤한 위치로 이동 및 정원 그리기 동작을 초당 2회, 총 10번 자동으로 반복하되 메인UI가 프리징 상태가 되지 않도록 별도 쓰레드로 구현해야 합니다.
