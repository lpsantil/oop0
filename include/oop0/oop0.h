#ifndef	OOP0_H
#define	OOP0_H

#include <stdarg.h> /* va_list */

void* New( const void* _type, ... );
void* Delete( const void* obj );

struct Class;
struct EmptyObject;

typedef struct EmptyObject
{
   /* Parent so you can call the Parent constructor */
   const struct Class* type;
} EmptyObject;

typedef struct Class
{
   const struct Class* parent;
   void* ( *constructor )( const void* self, va_list* app );
   void* ( *destructor )( const void* self );
   char* name;
   unsigned int size;
   EmptyObject prototype;
} Class;

extern const Class EmptyObject$;

void* EmptyObjectConstructor( const void* self, va_list* app );
void* EmptyObjectDestructor( const void* self );

/*************************/

#endif /*OOP0_H*/
