#!/usr/bin/mumps
	znumber
      write "Interpreter $next() and  $order() tests",!
      write "be sure there is a new global data base",!
      k ^a
      for i=1:1:10 s ^a(i)=i s a(i)=i
      set x="w ""next ^a(-1) expect 1 >>>"",$n(^a(-1)),!"
      x x
      set x="w ""next ^a(1) expect 2 >>>"",$n(^a(1)),!"
      x x
      set x="w ""next ^a(9) expect 10 >>>"",$n(^a(9)),!"
      x x
      set x="w ""next ^a(10) expect -1 >>>"",$n(^a(10)),!"
      x x
      set x="w ""order ^a("""") expect 1 >>>"",$o(^a("""")),!"
      x x
      set x="w ""order ^a(1) expect 2 >>>"",$o(^a(1)),!"
      x x
      set x="w ""order ^a(9) expect 10 >>>"",$o(^a(9)),!"
      x x
      set x="w ""order ^a(10) expect empty >>>"",$o(^a(10)),!"
      x x
      set x="w ""order -1 ^a(10) expect 9 >>>"",$o(^a(10),-1),!"
      x x
      set x="w ""order 1 ^a(10) expect empty >>>"",$o(^a(10),1),!"
      x x
      set x="w ""order 0-1 ^a(10) expect 9 >>>"",$o(^a(10),0-1),!"
      x x
      set x="w ""order ^a($n(^a(-1)) expect 2 >>>"",$o(^a($n(^a(-1))),1),!"
      x x
      write "====== local tests==========",!
      set x="w ""next a(-1) expect 1 >>>"",$n(a(-1)),!"
      x x
      set x="w ""next a(1) expect 2 >>>"",$n(a(1)),!"
      x x
      set x="w ""next a(9) expect 10 >>>"",$n(a(9)),!"
      x x
      set x="w ""next a(10) expect -1 >>>"",$n(a(10)),!"
      x x
      set x="w ""order a("""") expect 1 >>>"",$o(a("""")),!"
      x x
      set x="w ""order a(1) expect 2 >>>"",$o(a(1)),!"
      x x
      set x="w ""order a(9) expect 10 >>>"",$o(a(9)),!"
      x x
      set x="w ""order a(10) expect empty >>>"",$o(a(10)),!"
      x x
      set x="w ""order -1 a(10) expect 9 >>>"",$o(a(10),-1),!"
      x x
      set x="w ""order 1 a(10) expect empty >>>"",$o(a(10),1),!"
      x x
      set x="w ""order 0-1 a(10) expect  9 >>>"",$o(a(10),0-1),!"
      x x
      set x="w ""order a($n(^a(-1)) expect 2 >>>"",$o(a($n(^a(-1))),1),!"
      x x
