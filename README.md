# EventDrivenSimulator
Smart Factory Simulation (singleton architecture)

제한된 시간 내에 이벤트 큐에 enqueue된 이벤트들을 순차적으로 실행한다.

이는 Simengine클래스의 instance를 통해 단일 객체 (싱글톤) 방식으로 진행된다. 

main에서 Simengine 인스턴스에 각 모델을 추가하고, 실행하게되면 Generator에서 처음 initialize된다.

Machine, Product, Product Input Output Rule, Map 등이 Generate되며, 

추상 클래스 EoModel을 상속받는 rule에 의해 schedule 메소드가 실행되면 handle 메소드가 호출된다. 

Generator에서는 유휴상태인 Machine 인스턴스를 반복적으로 찾으며 Product 생산을 요청한다.

요청된 정보에는 Machine ptr이 포함되며 Machine에서는 Product Input Output Rule에 의해 가장 우선순위가 높은 공정을 통해 제품을 출력한다.



24.04.30 - AGV는 아직 고려하지 않은 시뮬레이션 모델 기초 틀을 작성하였음. Machine에서 우선순위에 따라 높은 공정을 출력하는 부분 구현 필요.
