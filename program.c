DFA AUTOMATA [
	states: {  r, o, j , >s , *w, *q },
	alphabet: { a, b },
	transitions: {
        |q|-a->|r| ,  
        |w|<-b->|r|,      
        |s|-a->|{w,q}|
    }
];
