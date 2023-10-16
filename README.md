# 메탈슬러그2 모작

<p align="center">
  <br>
  <img src="https://github.com/thesun007/metal-slug/assets/39186061/2a131ebb-a93b-499b-8180-20fb9726a9c3.png">
  <br>
</p>
<p align="center">
[video](https://thesun007.tistory.com/39)
</p>


<br>

## 기술 스택

| JavaScript | TypeScript |  React   |  Node   |
| :--------: | :--------: | :------: | :-----: |
|   ![js]    |   ![ts]    | ![react] | ![node] |

<br/>

## 구현 기능

### 플레이어 상체 & 하체
<img src="https://github.com/thesun007/metal-slug/assets/39186061/f126b630-ec59-4232-b17f-d5f494972753">  


플레이어 상체 업데이트 로직 요약  
<img src="https://github.com/thesun007/metal-slug/assets/39186061/06cb69a1-e7f6-49f5-a71f-651dbe7b733d" width="500px" height="800px">  


> - 모션 결정 과정
> 	1. (점프 상태일 때/아닐 때 따로) 방향 키/점프 키 입력에 따른 움직임 모션 결정.
> 	1. 공격 키/수류탄 키 입력에 따른 모션 결정.
> 	1. 공격 모션이 끝났을 때, 공격상태 값 제거.
> 	1. 반대 모션이 필요하여, 프레임을 거꾸로 진행하게 하는 리버스 기능 추가.
> 	1. 한 사이클만 프레임 애니메이션을 진행하는 렌더링 기능 추가 ( 예_ 점프 모션)

> + 이동 위치 계산 과정
>	1. 방향 키 입력에 따른 위치(x, y)값 결정
>	2. 일어선 상태/앉은 상태에 따라 속도 변경.
>	3. 특정 모션(앉는 중, 앉아서 공격 등)일 땐, 잠시 위치 고정

> + 총알, 수류탄 생성 과정
>	1. 근접 공격 모션일 경우, 바로 적 충돌 체크.
>	2. 일반 공격 모션일 경우, 피스톨/기관총 모드에 따라 다른 총알 생성.
>	3. 위로 쏘기/아래로 쏘기/대각 쏘기 모션에 따라 총알 각도 차등 적용.
>	4. 수류탄 모션일 경우, 수류탄 생성 

> + 점프, 라인 충돌 과정
>	1. 포물선 운동에 따른 높이 값(y) 추가 계산.
>	2. 직선의 방정식에 따른 바닥 적용.(y 고정)  
  
플레이어 하체 업데이트 로직 요약
> + 모션 결정 과정
>	1. (점프 상태일 때/아닐 때 따로) 방향 키/점프 키 입력에 따른 움직임 모션 결정.
>	2. 공격 키/수류탄 키 입력에 따른 모션 결정.

> + 객체 이동 
>	1. 상체의 월드행렬을 참조해서 부모로 적용함.  
--- 
### 아라비안
아라비안 업데이트 로직 요약
> + 모션 결정 과정
>	1. 플레이어 방향으로 방향 전환 모션 적용.
>	2. 방향 전환 후, 아라비안 AI 클래스 Update 진행.
>	3. 공격 모션 결정 시, 상태를 “Attack＂또는 “Throwing”으로 변경
> + 이동 위치 계산 과정
>	1. 점프/백스탭/셔플/Run 모션에 따라 위치 값 결정
> + 공격 과정
>	1. 결정된 공격 모션에 따라 투척 칼 생성 or 근접공격
> + AI 과정 요약
<img src="https://github.com/thesun007/metal-slug/assets/39186061/c046d712-9348-41a7-8011-7d063433d40b">  

---  
### NPC
> - 모션 결정 과정
>	1. NPC AI [Wait] 클래스 상태로 시작.
>	2. 포박(Wait) 모션을 플레이어가 풀어 줄 때 까지 유지.
>	3. 풀려났을 때, AI 규칙에 따라 행동  

> - 이동 위치 계산 과정
>	1. 걷기/달리기 모션에 따라 이동속도 차등 적용.  

> - 아이템 제공 과정
>	1. NPC 클래스의 Gift 옵션에 따라 기관총 탄약 또는 수류탄 박스 아이템 제공  

> - AI 과정 요약
![스크린샷 2023-10-16 231942](https://github.com/thesun007/metal-slug/assets/39186061/55436c6a-2b15-4599-bf43-a33fc6f337e7)

---
### BOSS


<br>

## 배운 점 & 아쉬운 점
### 배운 점
<p align="justify">

</p>
### 아쉬운 점
<p align="justify">

<br>

## 라이센스

MIT &copy; [NoHack](mailto:lbjp114@gmail.com)

<!-- Stack Icon Refernces -->

[js]: /images/stack/javascript.svg
[ts]: /images/stack/typescript.svg
[react]: /images/stack/react.svg
[node]: /images/stack/node.svg
