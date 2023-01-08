#include <stdio.h>
#include <assert.h>
#include <oop0/oop0.h>

/*
#define BLOCK_BITMAP_ENTRY_SIZE ( sizeof( void* ) )

#if ( sizeof( void* ) == 8 )
#elif ( sizeof( void* ) == 4 )
#else
#error BLOCK_BITMAP_ENTRY_SIZE not supported
#endif
*/
const struct Object$_t Object$;

typedef struct Object_t
{
   /* Inheritance */
   EmptyObject;

   /* Extension */
   int value;
   char* ( *toString )( const void* self );
} Object;

void* Object__Constructor( const void* self, va_list* app )
{
   int x = va_arg( *app, int );
   Object* o = ( Object* )( self );
   assert( o );
   o->value = x;
   return( ( void* )( self ) );
}

void* Object__Destructor( const void* self )
{
   Object* o = ( Object* )( self );
   assert( o );
   o->type->parent->destructor( self );
   return( NULL );
}

char* Object__toString( const void* self )
{
   return( "[object Object]" );
}

typedef struct Object$_t
{
   /* Inheritance */
   const struct Class* parent;
   void* ( *constructor )( const void* self, va_list* app );
   void* ( *destructor )( const void* self );
   char* name;
   unsigned int size;
   Object prototype;
   /* Static extension */
   unsigned int ver;
   unsigned int ( *getSize )( void );
} Object$_;

unsigned int Object$__getSize( void )
{
   return( Object$.size );
}

const struct Object$_t Object$ =
{
   .name = "Object",
   .size = sizeof( Object ),

   .prototype.type = ( Class* )( &Object$ ),
   .parent = ( Class* )( &EmptyObject$ ),
   .constructor = Object__Constructor,
   .destructor = Object__Destructor,
   .prototype.value = 0,
   .prototype.toString = Object__toString,
   .ver = 1,
   .getSize = Object$__getSize,
};

int main( int argc, char** argv )
{
   Object* o;

   printf( "Object(%li)\n"
           "void*(%li)\n"
           "int(%li)\n"
           "long int(%li)\n"
           "long long int(%li)\n"
           "Object$(%li)\n"
           "\n",
           sizeof( Object ),
           sizeof( void* ),
           sizeof( int ),
           sizeof( long int ),
           sizeof( long long int ),
           sizeof( struct Object$_t ) );

   o = New( &Object$, 5 );

   printf( "nm(%s)\n",
           o->toString( o ) );

   return( 0 );
}
