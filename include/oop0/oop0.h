#ifndef	OOP0_H
#define	OOP0_H

#include <stdarg.h> /* va_list */

void* New( const void* _type, ... );
void* Delete( const void* obj );
/*
struct Class;
struct EmptyObject;
*/
typedef struct EmptyObject_t
{
   /* Parent so you can call the Parent constructor */
   const struct Class* type;
} EmptyObject;

typedef struct Class
{
   const struct Class* parent;
   void* ( *ctor )( const void* self, va_list* app );
   void* ( *dtor )( const void* self );
   char* name;
   unsigned int size;
   EmptyObject prototype;
} Class;

extern const Class EmptyObject$;

void* EmptyObjectCtor( const void* self, va_list* app );
void* EmptyObjectDtor( const void* self );

/*************************/

#endif /*OOP0_H*/
