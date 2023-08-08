// Krytog, 2023


#include "Interfaces/MinimapVisible.h"

uint32 GetTypeHash(const IMinimapVisible* Object)
{
    return GetTypeHash(Cast<AActor>(Object)); // All MinimapVisible objects are actors
}

bool IMinimapVisible::operator==(const IMinimapVisible* Object) const
{
    return Cast<AActor>(this) == Cast<AActor>(Object); // All MinimapVisible objects are actors
}
