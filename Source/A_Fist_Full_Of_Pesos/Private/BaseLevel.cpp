// Completa tu aviso de copyright en la p�gina de Descripci�n de la Configuraci�n del Proyecto.

#include "BaseLevel.h" // Incluye la cabecera de la clase ABaseLevel.
#include "Components/BoxComponent.h" // Incluye la cabecera para los componentes de colisi�n BoxComponent.

// Establece valores predeterminados
ABaseLevel::ABaseLevel()
{
	// Configura este actor para llamar a Tick() cada cuadro. Puedes desactivar esto para mejorar el rendimiento si no lo necesitas.
	PrimaryActorTick.bCanEverTick = true; // Permite que el actor realice operaciones cada cuadro.
}

// Llamado cuando el juego comienza o cuando se genera
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay(); // Llama a la implementaci�n de BeginPlay de la clase base.

	// Si el componente Trigger no es nulo, oculta su visualizaci�n en el juego.
	if (Trigger != nullptr)
		Trigger->bHiddenInGame = true;
}

// Llamado cada cuadro
void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Llama a la implementaci�n de Tick de la clase base.

	// Aqu� puedes agregar l�gica que se ejecute cada cuadro.
}

UBoxComponent * ABaseLevel::GetTrigger()
{
	return Trigger;
}

UBoxComponent * ABaseLevel::GetSpawnLocation()
{
	return SpawnLocation;
}
