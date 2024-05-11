#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* ----------------------------------------------- DEFINITION SET ----------------------------------------------- */

DefinitionSet * DefinitionSetSemanticAction(Definition * definition1, DefinitionSet * set2) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefinitionSet * set = calloc(1, sizeof(DefinitionSet));
	DefinitionNode * node = calloc(1, sizeof(DefinitionNode));
	node->definition = definition1;
	node->next = set2->first;
	set->first = node;
	set->tail = set2->tail;
	return set;
}

DefinitionSet * SingularDefinitionSetSemanticAction(Definition * definition) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	DefinitionSet * set = calloc(1, sizeof(DefinitionSet));
	DefinitionNode * node = calloc(1, sizeof(DefinitionNode));
	node->definition = definition;
	set->first = node;
	set->tail = node;
	return set;
}

/* ------------------------------------------------- DEFINITION ------------------------------------------------- */


Definition * StateSetDefinitionSemanticAction(char * identifier, StateSet * set) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Definition * definition = calloc(1, sizeof(Definition));
	set->identifier = identifier;
	definition->stateSet = set;
	definition->type = STATE_DEFINITION;
	return definition;
}

Definition * SingularStateSetDefinitionSemanticAction(char * identifier, State* state) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateExpression * stateExpression = SingularStateExpressionSemanticAction(state);
	StateNode * first = SingularExpressionStateNodeSemanticAction(stateExpression);
	StateSet * set = NodeStateSetSemanticAction(first);	
	return StateSetDefinitionSemanticAction(identifier, set);
}

Definition * SymbolSetDefinitionSemanticAction(char * identifier, SymbolSet * set) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Definition * definition = calloc(1, sizeof(Definition));
	set->identifier = identifier;
	definition->symbolSet = set;
	definition->type = ALPHABET_DEFINITION;
	return definition;
}

Definition * SingularSymbolSetDefinitionSemanticAction(char * identifier, Symbol * symbol) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolExpression* symbolExpression = SingularSymbolExpressionSemanticAction(symbol);
	SymbolNode * first = SingularExpressionSymbolNodeSemanticAction(symbolExpression);
	SymbolSet * set = NodeSymbolSetSemanticAction(first);		
	return SymbolSetDefinitionSemanticAction(identifier, set);
}

Definition * TransitionSetDefinitionSemanticAction(char * identifier, TransitionSet * set) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Definition * definition = calloc(1, sizeof(Definition));
	set->identifier = identifier;
	definition->transitionSet = set;
	definition->type = TRANSITION_DEFINITION;
	return definition;
}

Definition * SingularTransitionSetDefinitionSemanticAction(char * identifier, Transition * transition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionExpression * transitionExpression = SingularTransitionExpressionSemanticAction(transition);
	TransitionNode * first = SingularExpressionTransitionNodeSemanticAction(transitionExpression);
	TransitionSet * set = NodeTransitionSetSemanticAction(first);
	return TransitionSetDefinitionSemanticAction(identifier, set);
}

Definition * AutomataDefinitionSemanticAction(AutomataType type, char * identifier, Automata * automata ) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Definition * definition = calloc(1, sizeof(Definition));
	automata->identifier = identifier;
	automata->automataType = type;
	definition->automata = automata;
	definition->type = AUTOMATA_DEFINITION;
	return definition;
}

/*-------------- CONVERSION DE TOKEN A ENUM ----------------------------*/
StateType stateTypeSemanticAction(StateType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	return type;
}

/* ------------------------------------------------- AUTOMATA ------------------------------------------------- */


Automata * AutomataSemanticAction( StateExpression* states, SymbolExpression* alphabet, TransitionExpression* transitions) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Automata * automata = calloc(1, sizeof(Automata));
	automata->states = states;
	automata->alphabet = alphabet;
	automata->transitions = transitions;
	return automata;
}

AutomataType AutomataTypeAction(AutomataType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	return type;
}


/* ------------------------------------------------- EXPRESSIONS ------------------------------------------------- */

/*---------------------------EXPRESIONES QUE REPRESENTAN UNA OPERACIÓN ENTRE CONJUNTOS-------------*/

TransitionExpression * TransitionExpressionSemanticAction(TransitionExpression * leftExpression, TransitionExpression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionExpression * expression = calloc(1, sizeof(TransitionExpression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

StateExpression * StateExpressionSemanticAction(StateExpression * leftExpression, StateExpression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateExpression * expression = calloc(1, sizeof(StateExpression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

SymbolExpression * SymbolExpressionSemanticAction(SymbolExpression * leftExpression, SymbolExpression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolExpression * expression = calloc(1, sizeof(SymbolExpression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

/*----------------EXPRESIONES QUE REPRESENTAN UN SUBCONJUNTO DE ELEMENTOS ------------------*/
//conjunto de transiciones per se (al menos es un subconjunto)
TransitionExpression * SetTransitionExpressionSemanticAction(TransitionSet * transitionSet){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionExpression * expression = calloc(1, sizeof(TransitionExpression));
	expression->transitionSet = transitionSet;
	expression->type = SET_EXPRESSION;
	return expression;
}

//conjunto de símbolos per se (al menos es un subconjunto)
SymbolExpression * SetSymbolExpressionSemanticAction(SymbolSet * symbolSet){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolExpression * expression = calloc(1, sizeof(SymbolExpression));
	expression->symbolSet= symbolSet;
	expression->type = SET_EXPRESSION;
	return expression;
}

//conjuto de estados per se (al menos es un subconjunto)
StateExpression * SetStateExpressionSemanticAction(StateSet * stateSet){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateExpression * expression = calloc(1, sizeof(StateExpression));
	expression->stateSet = stateSet;
	expression->type = SET_EXPRESSION;
	return expression;
}

/*---------------------------EXPRESIONES QUE REPRESENTAN UN ELEMENTO SUELTO --------------------*/

TransitionExpression * SingularTransitionExpressionSemanticAction(Transition * transition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionExpression * expression = calloc(1, sizeof(TransitionExpression));
	//acá podría agarrar y copiar el set 
	expression->transition = transition;
	expression->type = ELEMENT_EXPRESSION;
	return expression;
}

StateExpression * SingularStateExpressionSemanticAction(State * state){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateExpression * expression = calloc(1, sizeof(StateExpression));
	expression->state = state; 
	expression->type = ELEMENT_EXPRESSION;
	return expression;
}

SymbolExpression* SingularSymbolExpressionSemanticAction(Symbol * symbol){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolExpression* expression = calloc(1, sizeof(SymbolExpression));
	expression->symbol = symbol;
	expression->type = ELEMENT_EXPRESSION;
	return expression;
}

/* ------------------------------------------------- SETS ------------------------------------------------- */


/*----- CONJUNTOS CON UN ELEMENTO (NODO) ------*/
TransitionSet * SingularTransitionSetSemanticAction(Transition * transition){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionNode* transitionNode = calloc(1, sizeof(TransitionNode));
	transitionNode->transition = transition;
	transitionNode->type = ELEMENT;
	return NodeTransitionSetSemanticAction(transitionNode);
}

StateSet * SingularStateSetSemanticAction(State * state){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateNode* stateNode = calloc(1, sizeof(StateNode));
	stateNode->state = state;
	stateNode->type = ELEMENT;
	return NodeStateSetSemanticAction(stateNode);
}

SymbolSet * SingularSymbolSetSemanticAction(Symbol * symbol){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolNode* symbolNode = calloc(1, sizeof(SymbolNode));
	symbolNode->symbol = symbol;
	symbolNode->type = ELEMENT;
	return NodeSymbolSetSemanticAction(symbolNode);
}



/*----- CONJUNTOS CON AL MENOS UN ELEMENTO (NODO) ------*/
SymbolSet * NodeSymbolSetSemanticAction(SymbolNode * symbolNode) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolSet * symbolSet = calloc(1, sizeof(SymbolSet));
	symbolSet->first= symbolNode;
	symbolSet->tail = symbolNode;
	return symbolSet;
}

StateSet * NodeStateSetSemanticAction(StateNode * stateNode) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateSet * stateSet = calloc(1, sizeof(StateSet));
	stateSet->first= stateNode;
	stateSet->tail = stateNode;
	//hay que revisar de que manera armar esto cuando se tenga más de un nodo y quiera dejar en sets separados (para despues acceder con .final, .initial, etc)
//	stateSet->stateType = stateNode->isFinal ? FINAL : state->isInitial ? INITIAL : REGULAR;
	return stateSet;
}

TransitionSet * NodeTransitionSetSemanticAction(TransitionNode * transitionNode) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionSet * transitionSet = calloc(1, sizeof(TransitionSet));
	transitionSet->first= transitionNode;
	transitionSet->tail = transitionNode;
	return transitionSet;
}

/*----------------- CONJUNTOS VACIOS -------------------*/
//se podría manejar una lista con un solo nodo que en particular sea una expressión vacía pero con esto debería andar
TransitionSet * EmptyTransitionSetSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TransitionSet* emptySet = calloc(1, sizeof(TransitionSet));	
	return emptySet;
}

StateSet * EmptyStateSetSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateSet * emptySet = calloc(1, sizeof(StateSet));
	return emptySet;
}

SymbolSet * EmptySymbolSetSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolSet * emptySet = calloc(1, sizeof(SymbolSet));
	return emptySet;
}

/*--------------- CONJUNTO DEFINIDO POR IDENTIFIER-------------------*/

TransitionSet * IdentifierTransitionSetSemanticAction(char * identifier){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	//si, se podría llamar a los empty pero es solo una linea la que me ahorro y me enchastra el logging
	TransitionSet* emptySet = calloc(1, sizeof(TransitionSet));	
	emptySet->identifier = identifier;
	//en el back se busca con la tablita que elementos tiene 
	return emptySet;
}

StateSet * IdentifierStateSetSemanticAction(char * identifier){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateSet * emptySet = calloc(1, sizeof(StateSet));
	emptySet->identifier = identifier;
	return emptySet;
}

SymbolSet * IdentifierSymbolSetSemanticAction(char* identifier){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	SymbolSet * emptySet = calloc(1, sizeof(SymbolSet));
	emptySet->identifier = identifier;
	return emptySet;
}

/*--------------- CONJUNTO A PARTIR DE DOBLE TRANSITION-------------------*/
TransitionSet * BothSideTransitionSemanticAction(StateExpression *left, StateExpression *right, SymbolExpression *alphabet){
	_logSyntacticAnalyzerAction(__FUNCTION__);	
	Transition * transitionToLeft = LeftTransitionSemanticAction(left,right,alphabet);
	Transition * transitionToRight = RightTransitionSemanticAction(left,right,alphabet);
	TransitionExpression * transitionToLeftExpression = SingularTransitionExpressionSemanticAction(transitionToLeft);
	TransitionExpression * transitionToRightExpression = SingularTransitionExpressionSemanticAction(transitionToRight);
	TransitionNode * transitionToRightNode = SingularExpressionTransitionNodeSemanticAction(transitionToRightExpression); 
	TransitionNode * transitionToLeftNode = ExpressionsTransitionNodeSemanticAction(transitionToLeftExpression, transitionToRightNode);
	TransitionSet * transitionSet = NodeTransitionSetSemanticAction(transitionToLeftNode);
	
	return transitionSet;
}

/*-------------------------------------------------- NODES ------------------------------------------------ */

/*-----------NODOS UNICOS QUE COMPONEN UN CONJUNTO (ÚLTIMO ELEMENTO) ---------------*/
//formo set a partir de una sola transition expression
TransitionNode * SingularExpressionTransitionNodeSemanticAction(TransitionExpression * transitionExpression){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	/*
	if (transitionExpression->type == SET_EXPRESSION || transitionExpression->type == VOID_EXPRESSION) {
		//cubre casos state, empty y stateSet
		//no haría falta alocar memoria porque ya lo hice anteriormente 
		return transitionExpression->transitionSet;
	}
	//cubro casos UNION, INTERSECTION y DIFFERENCE
	TransitionSet * transitionSet = calloc(1, sizeof(TransitionSet));
	*/
	TransitionNode * node = calloc(1, sizeof(TransitionNode));
	node->transitionExpression = transitionExpression;
	node->type = EXPRESSION;
	return node;
}


//formo set a partir de una sola state expression
StateNode * SingularExpressionStateNodeSemanticAction(StateExpression * stateExpression){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	/*
	if (stateExpression->type == SET_EXPRESSION || stateExpression->type == VOID_EXPRESSION) {
		//cubre casos state, empty y stateSet
		//no haría falta alocar memoria porque ya lo hice anteriormente 

		//sino quedaría algo así
		//StateSet * stateSet = calloc(1, sizeof(StateSet));
		//stateSet->states = stateExpression->stateSet->states;
		//stateSet->tail = stateExpression->stateSet->tail;		

		return stateExpression->stateSet;
	}
	//cubro casos UNION, INTERSECTION y DIFFERENCE
	StateSet * stateSet = calloc(1, sizeof(StateSet));
	*/
	StateNode * node = calloc(1, sizeof(StateNode));
	node->stateExpression = stateExpression;	
	node->type = EXPRESSION;
	return node;
}

//formo un nodo a partir de una sola symbol expression
SymbolNode * SingularExpressionSymbolNodeSemanticAction(SymbolExpression * symbolExpression){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	/*
	if (symbolExpression->type == SET_EXPRESSION || symbolExpression->type == VOID_EXPRESSION) {
		//cubre casos state, empty y stateSet
		//no haría falta alocar memoria porque ya lo hice anteriormente 
		return symbolExpression->symbolSet;
	}
	//cubro casos UNION, INTERSECTION y DIFFERENCE
	SymbolSet * symbolSet = calloc(1, sizeof(SymbolSet));
	*/
	SymbolNode * node = calloc(1, sizeof(SymbolNode));
	node->symbolExpression = symbolExpression;
	node->type = EXPRESSION;
	return node;
}

/*----------- NODOS INTERMEDIOS QUE CONECTAN CON EL SIGUIENTE ----------------*/
//formo set con 2 subconjuntos de tipo transition
TransitionNode * ExpressionsTransitionNodeSemanticAction(TransitionExpression * exp, TransitionNode * nextNode){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	//solo aloco memoria nueva porque necesito el identificador pero los nodos ya están creados
	TransitionNode * node = calloc(1, sizeof(TransitionNode));	
	node->transitionExpression= exp;
	node->type = EXPRESSION;
	//conecto los nodos con los subconjuntos
	node->next = nextNode;
	return node;
}

//formo set con 2 subconjuntos de tipo state
StateNode * ExpressionsStateNodeSemanticAction(StateExpression* exp, StateNode* nextNode){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	//solo aloco memoria nueva porque necesito el identificador pero los nodos ya están creados
	StateNode * node = calloc(1, sizeof(StateNode));
	node->stateExpression= exp;
	node->type = EXPRESSION;
	//conecto los nodos con los subconjuntos
	node->next = nextNode;
	return node;
}

//formo set con 2 subconjuntos de tipo symbol
SymbolNode * ExpressionsSymbolNodeSemanticAction(SymbolExpression* exp, SymbolNode* nextNode){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	//solo aloco memoria nueva porque necesito el identificador pero los nodos ya están creados
	SymbolNode * node = calloc(1, sizeof(SymbolNode));
	node->symbolExpression = exp;
	//todo: revisar si se puede especificar mejor chequeando el tipo de exp
	node->type = EXPRESSION;
	//conecto los nodos 
	node->next = nextNode;
	return node;
}

/*-----------------------CONJUNTO DE ESTADOS DE UN AUTOMATA POR TIPO--------------------*/
StateSet * StateTypeSetSemanticAction(char * identifier, StateType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StateSet * stateSet = calloc(1, sizeof(StateSet));
	stateSet->identifier = identifier;
	stateSet->stateType = type;
	return stateSet;
}

/* ------------------------------------------------- ELEMENTS ------------------------------------------------- */


State * StateSemanticAction(boolean isInitial, boolean isFinal, Symbol * symbol){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	State * state = calloc(1, sizeof(State));
	state->isFinal = isFinal;
	state->isInitial = isInitial;
	state->symbol = *symbol;
	return state;
}

Symbol * LambdaSemanticAction() {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Symbol * symbol = calloc(1, sizeof(Symbol));
	symbol->value= LAMBDA_STRING;
	return symbol;
}


Symbol * SymbolSemanticAction(char * value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Symbol * symbol = calloc(1, sizeof(Symbol));
	symbol->value = value;
	return symbol;
}

// se tiene que mandar un TransitionSet donde ya parseo las transitions en individuales (estado -simbolo-> estado) lo que me sirve para en el 
// backend hacer el manejo de operaciones con conjuntos de transiciones 
Transition * LeftTransitionSemanticAction(StateExpression * left, StateExpression * right, SymbolExpression * alphabet){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Transition * transition = calloc(1, sizeof(Transition));	
	transition->fromExpression= right;
	transition->toExpression= left;
	transition->symbolExpression = alphabet;
	return transition;
}

Transition * RightTransitionSemanticAction(StateExpression *left, StateExpression *right, SymbolExpression *alphabet){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Transition * transition = calloc(1, sizeof(Transition));
	transition->fromExpression= left;
	transition->toExpression= right;
	transition->symbolExpression = alphabet;
	return transition;	
}
/*
TransitionExpression * BothSideTransitionSemanticAction(StateExpression *left, StateExpression *right, SymbolExpression *alphabet){
	_logSyntacticAnalyzerAction(__FUNCTION__);	
	Transition * transitionToLeft = LeftTransitionSemanticAction(left,right,alphabet);
	Transition * transitionToRight = RightTransitionSemanticAction(left,right,alphabet);
	TransitionExpression * transitionToLeftExpression = SingularTransitionExpressionSemanticAction(transitionToLeft);
	TransitionExpression * transitionToRightExpression = SingularTransitionExpressionSemanticAction(transitionToRight);
	TransitionNode * transitionToRightNode = SingularExpressionTransitionNodeSemanticAction(transitionToRightExpression); 
	TransitionNode * transitionToLeftNode = ExpressionsTransitionNodeSemanticAction(transitionToLeftExpression, transitionToRightNode);
	TransitionSet * transitionSet = NodeTransitionSetSemanticAction(transitionToLeftNode);
	return SetTransitionExpressionSemanticAction(transitionSet);
} */

/* ------------------------------------------------- PROGRAM ------------------------------------------------- */

// se tendría que manejar un conjunto de definiciones como resultado de un programa que luego se resuelven en el back
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, DefinitionSet* definitionSet) {
//Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Definition* definition) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->definitionSet = definitionSet;
	//program->definition = definition;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}

