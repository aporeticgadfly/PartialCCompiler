#include <stdio.h>

int dbgflag = 0;

void syntrace(char* string) {
	if (dbgflag == 1) {
		printf('%s\n', string);
	}
}

extern void translationUnit() {
	syntrace("<translationUnit>");
}

extern void externalDeclaration() {
	syntrace("<externalDeclaration>");
}

extern void functionDefinition() {
	syntrace("<functionDefinition>");
}

extern void declarationSpecifier() {
	syntrace("<declarationSpecifier>");
}

extern void storageClassSpecifier() {
	syntrace("<storageClassSpecifier>");
}

extern void typeSpecifier() {
	syntrace("<typeSpecifier>");
}

extern void structOrUnionSpecifier() {
	syntrace("<structOrUnionSpecifier>");
}

extern void structOrUnion() {
	syntrace("<structOrUnion>");
}

extern void structDeclaration() {
	syntrace("<structDeclaration>");
}

extern void specifierQualifier() {
	syntrace("<specifierQualifier>");
}

extern void structDeclaratorList() {
	syntrace("<structDeclaratorList>");
}

extern void structDeclarator() {
	syntrace("<structDeclarator>");
}

extern void declarator() {
	syntrace("<declarator>");
}

extern void pointer() {
	syntrace("<pointer>");
}

extern void typeQualifier() {
	syntrace("<typeQualifier>");
}

extern void directDeclarator() {
	syntrace("<directDeclarator>");
}

extern void constantExpression() {
	syntrace("<constantExpression>");
}

extern void conditionalExpression() {
	syntrace("<conditionalExpression>");
}

extern void logicalOrExpression() {
	syntrace("<logicalOrExpression>");
}

extern void logicalAndExpression() {
	syntrace("<logicalAndExpression>");
}

extern void inclusiveOrExpression() {
	syntrace("<inclusiveOrExpression>");
}

extern void exclusiveOrExpression() {
	syntrace("<exclusiveOrExpression>");
}

extern void andExpression() {
	syntrace("<andExpression>");
}

extern void equalityExpression() {
	syntrace("<equalityExpression>");
}

extern void relationalExpression() {
	syntrace("<relationalExpression>");
}

extern void shiftExpression() {
	syntrace("<shiftExpression>");
}

extern void additiveExpression() {
	syntrace("<additiveExpression>");
}

extern void multiplicativeExpression() {
	syntrace("<multiplicativeExpression>");
}

extern void castExpression() {
	syntrace("<castExpression>");
}

extern void unaryExpression() {
	syntrace("<unaryExpression>");
}

extern void postfixExpression() {
	syntrace("<postfixExpression>");
}

extern void primaryExpression() {
	syntrace("<primaryExpression>");
}

extern void constant() {
	syntrace("<constant>");
}

extern void expression() {
	syntrace("<expression>");
}

extern void assignmentExpression() {
	syntrace("<assignmentExpression>");
}

extern void assignmentOperator() {
	syntrace("<assignmentOperator>");
}

extern void unaryOperator() {
	syntrace("<unaryOperator>");
}

extern void typeName() {
	syntrace("<typeName>");
}

extern void parameterTypeList() {
	syntrace("<parameterTypeList>");
}

extern void parameterList() {
	syntrace("<parameterList>");
}

extern void parameterDeclaration() {
	syntrace("<parameterDeclaration>");
}

extern void abstractDeclarator() {
	syntrace("<abstractDeclarator>");
}

extern void directAbstractDeclarator() {
	syntrace("<directAbstractDeclarator>");
}

extern void enumSpecifier() {
	syntrace("<enumSpecifier>");
}

extern void enumeratorList() {
	syntrace("<enumeratorList>");
}

extern void enumerator() {
	syntrace("<enumerator>");
}

extern void typedefName() {
	syntrace("<typedefName>");
}

extern void declaration() {
	syntrace("<declaration>");
}

extern void initDeclarator() {
	syntrace("<initDeclarator>");
}

extern void initializer() {
	syntrace("<initializer>");
}

extern void initializerList() {
	syntrace("<initializerList>");
}

extern void compoundStatement() {
	syntrace("<compoundStatement>");
}

extern void statement() {
	syntrace("<statement>");
}

extern void labeledStatement() {
	syntrace("<labeledStatement>");
}

extern void expressionStatement() {
	syntrace("<expressionStatement>");
}

extern void selectionStatement() {
	syntrace("<selectionStatement>");
}

extern void iterationStatement() {
	syntrace("<iterationStatement>");
}

extern void jumpStatement() {
	syntrace("<jumpStatement>");
}