#include "Obstacle.h"

// Establece valores predeterminados
AObstacle::AObstacle()
{
    // Configura este actor para llamar a Tick() cada cuadro. Puedes desactivar esto para mejorar el rendimiento si no lo necesitas.
    PrimaryActorTick.bCanEverTick = true;
}

// Llamado cuando el juego comienza o cuando se genera
void AObstacle::BeginPlay()
{
    Super::BeginPlay();
    // Aquí puedes agregar cualquier lógica de inicialización que necesites al inicio del juego
}

// Llamado cada cuadro
void AObstacle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Aquí puedes agregar cualquier lógica que necesites ejecutar cada cuadro
}
