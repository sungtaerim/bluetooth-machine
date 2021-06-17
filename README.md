# bluetooth-machine

Управляемая машина 

Машина управляется с помощью мобильного телефона. Соединение происходит с помощью bluetooth модуля HC-05.

Для проекта необходимо: 
  - плата Arduino UNO;
  - плата troyka shield;
  - плата motor shield (2 канала, 2 А);
  - платформа для робота;
  - 4 колеса;
  - 4 мотора-редуктора. 
  
Соединение плат происходит в виде "бутерброда": на Arduino приклепляется motor shield, далее сверху прикрепляется troyka shield.
Моторы соединяются по два на одну клемму. При этом одна пара моторов соединяется напрямую ("+" к "+"), вторая пара соединяется в обратном направлении ("+" к "-"). 

Питание для  Arduino 5В (power bank или USB порт компьютера), питание motor shield 9В.

  
