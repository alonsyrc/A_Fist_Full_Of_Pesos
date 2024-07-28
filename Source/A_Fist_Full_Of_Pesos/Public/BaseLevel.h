// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#pragma once

#include "CoreMinimal.h" // Incluye las definiciones básicas de Core.
#include "GameFramework/Actor.h" // Incluye la clase base AActor.
#include "BaseLevel.generated.h" // Genera el código necesario para la clase.

class UBoxComponent; // Declaración anticipada de UBoxComponent.

UCLASS()
class A_FIST_FULL_OF_PESOS_API ABaseLevel : public AActor // Define la clase ABaseLevel que hereda de AActor.
{
	GENERATED_BODY() // Macro que genera el código necesario para la clase.

public:
	// Establece valores predeterminados para las propiedades de este actor.
	ABaseLevel();

protected:
	// Llamado cuando el juego comienza o cuando el actor es generado.
	virtual void BeginPlay() override;

public:
	// Llamado cada cuadro.
	virtual void Tick(float DeltaTime) override;

protected:
	// Componente de colisión que actúa como disparador.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UBoxComponent* Trigger;

	// Componente de colisión que indica la ubicación de generación.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
		UBoxComponent* SpawnLocation;

public:
	// Devuelve el componente de disparador.
	UBoxComponent* GetTrigger();

	// Devuelve el componente de ubicación de generación.
	UBoxComponent* GetSpawnLocation();
};
