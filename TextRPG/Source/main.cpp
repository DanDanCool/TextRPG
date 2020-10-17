//This is a comment, '//' denotes a comment, this statement does not affect the code whatsoever

/*
 * This is also a comment
 * difference being that it is multiline
 * anything that appears in between the slash and the asterisk
 * will be a comment
 * You may also hear the term 'commented out' this is to refer to code that is put in comments
 * the stars are optional, they are more of a stylistic choice
 */

/*
 * The statement below is called a preprocessor statement, preprocessor statements are instructions
 * that the compiler will do at 'compile time.' Compile time is used to refer to when the compiler
 * reads through all of your code and generates code. Every '.cpp' file is compiled into what is called
 * a 'translation unit.' A translation unit is file that contains assembly code, but are unable to
 * be standalone programs. '.h' files are called header files, these will not be compiled into
 * translation units. '.h' files are referred to as Header files and '.cpp' files are referred to as
 * source files. Technically, the file extensions are completely arbitrary, for example, a '.h' file
 * could be compiled as a translation unit, if you really wanted to. But it is good to be consistent
 * so people know what the file contents are. There are also variants of the file extensions, such as
 * .cxx and .hpp for source files and header files respectively, and there is also the '.c' extension
 * for c source files.
 * Translation units are linked together by the linker, which creates a program from all the translation
 * units.
 * In this case, the preprocessor statement is the #include statement, this instructs the compiler
 * to copy and paste all of the contents in the following file into this file.
 * There are typically two notations for include statements, "file" and <file>. There are no real rules
 * as to when to use one opposed to the other, but generally the former is used to indicate that you are
 * including one of your own files, while the latter one is used to indicate that you are using a
 * library file.
 */

#include "Game.h"

/*
 * The function below is the 'main' function, as the name suggests, this is the entry point of the program,
 * all executable programs must define a 'main' function. The main function will typically return some
 * values depending on how your program run, typically, a negative return value means your program crashed,
 * while positive values mean your program ran without issue.
 * There are also different versions of the main function you can use, but you don't have to worry about them
 * for now.
 * The main function does not have to be defined in a file called 'main.cpp,' but that's generally where it is
 * defined;
 * 
 * All functions have a type that they return, with the exception of void. When a function is called, the block
 * of code within that function is executed.
 */

int main()
{
	/*
	 * This statement declares a new variable of type Game*, pronounced 'game pointer.' A pointer is a 64 bit
	 * integer that stores a memory address, we generally say a pointer points to a memory address, hence the
	 * name.
	 * There is two places where memory is stored, the stack and the heap. The stack is smaller than the heap,
	 * but it is much faster than it. If you allocate too much memory on the stack, you will get an error known
	 * as a 'stack overflow.'
	 * To avoid this, we generally store large objects on the heap. In addition, a variable defined on the stack
	 * only exists in its defined scope, the variable will be deleted once it goes 'out of scope'
	 * Example:
	 * 
	 * int main()
	 * {
	 *     int foo2 = 2;
	 *     {
	 *         int foo = 1;
	 *         foo2 = 2; //ok
	 *         foo = 3; //ok
	 *     } //foo deleted
	 *     foo = 2; //error
	 * } //foo2 deleted
	 * 
	 * The variable 'foo' is defined in the inner curly brackets, this creates an 'anonymous scope,' function
	 * blocks are also scopes, the main function itself is a scope. In this case, an anonymous scope was
	 * created inside the main scope as an inner scope.
	 * In addition, variables defined on the stack cannot be accessed outside of its scope, but as you saw in
	 * the example, variables can be accessed in inner scopes.
	 * Memory allocated on the heap can be accessed anywhere, but cannot be accessed directly, a pointer is
	 * required to point to the memory address of where the variable is stored. In addition, memory allocated
	 * on the heap must be deleted explicitly, not doing so is called a 'memory leak,' this is a very hard to
	 * detect problem. Other languages such as Java have a feature known as 'garbage collection,' but in C++
	 * you must manage your own memory. Luckily, C++ has a lot of features to manage memory, so if you're not
	 * feeling up to it, you can rely on the standard library to delete memory for you.
	 * If you forget to free any memory, the Operating System will reclaim everything once the program is
	 * finished running.
	 * In this case the game is not used anywhere else, and is relatively small, so it would have been fine to
	 * allocate it on the stack.
	 */

	Game* game = new Game();

	/* Calls the game's Run method, stack methods are called with dot notation while pointers use arrows.
	 * E.g.
	 * //stack
	 * Game game();
	 * game.Run();
	 * //heap
	 * Game* game = new Game();
	 * game->Run();
	 */

	game->Run();

	//game is allocated on the heap so it must be explicitly deleted
	delete game;
}

/*
 * Suggested browsing order:
 * 1. main.cpp
 * 2. Game.h
 * 3. Game.cpp
 * 4. Player.h
 * 5. Player.cpp
 * 6. StatusEffect.h
 * 7. Items/Item.h
 * 
 * After you are finished reading those files, you should be able to understand the code, please
 * ask my any questions on the JGDC discord!
 */