// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#include "BaseLevel.h" // Incluye la cabecera de la clase ABaseLevel.
#include "Components/BoxComponent.h" // Incluye la cabecera para los componentes de colisión BoxComponent.

// Establece valores predeterminados
ABaseLevel::ABaseLevel()
{
	// Configura este actor para llamar a Tick() cada cuadro. Puedes desactivar esto para mejorar el rendimiento si no lo necesitas.
	PrimaryActorTick.bCanEverTick = true; // Permite que el actor realice operaciones cada cuadro.
}

// Llamado cuando el juego comienza o cuando se genera
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay(); // Llama a la implementación de BeginPlay de la clase base.

	// Si el componente Trigger no es nulo, oculta su visualización en el juego.
	if (Trigger != nullptr)
		Trigger->bHiddenInGame = true;
}

// Llamado cada cuadro
void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Llama a la implementación de Tick de la clase base.

	// Aquí puedes agregar lógica que se ejecute cada cuadro.
}

// Devuelve el componente de disparador
UBoxComponent* ABaseLevel::GetTrigger()
{
	return Trigger; // Retorna la referencia al componente Trigger.
}

// Devuelve el componente de ubicación de generación
UBoxComponent* ABaseLevel::GetSpawnLocation()
{
	return SpawnLocation; // Retorna la referencia al componente SpawnLocation.
}
