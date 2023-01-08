/*#include <stdbool.h>*/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <oop0/oop0.h>   /* Class, EmptyObject, EmptyObject$ */

/********************************************************************/

void* New( const void* _type, ... )
{
   va_list ap;
   const Class* type = _type;
   EmptyObject* object;

   assert( type && type->size );                       /* Make sure we have a valid type with some size */
   object = malloc( 1 * type->size );                  /* 'New' its space */
   assert( object );                                   /* Make sure we didn't get NULL */
   object->type = type;                                /* Let the new object knows its type */
   memcpy( object, &( type->prototype ), type->size ); /* Copy its initial instance values */
   va_start( ap, _type );                              /* Setup the stack to call constructor */
   object = object->type->constructor( object, &ap );  /* Call the new object's constructor with the arguments passed to New */
   va_end( ap );                                       /* Re-adjust the stack */
   return( object );                                   /* Pass back the new, initalized object */
}

void* Delete( const void* obj )
{
   const EmptyObject* o = obj;
   assert( o );
   assert( o->type );
   assert( o->type->destructor );

   return( o->type->destructor( o ) );
}

const Class EmptyObject$ =
{
   .name = "{}",
   .size = sizeof( EmptyObject ),

   .prototype.type = ( Class* )( &EmptyObject$ ),
   .parent = NULL,
   .constructor = EmptyObjectConstructor,
   .destructor = EmptyObjectDestructor,
};

void* EmptyObjectConstructor( const void* self, va_list* app )
{
   return( ( void* )( self ) );
}

void* EmptyObjectDestructor( const void* self )
{
   assert( self != NULL );
   free( ( void* )( self ) );
   return( NULL );
}

/*************************/
