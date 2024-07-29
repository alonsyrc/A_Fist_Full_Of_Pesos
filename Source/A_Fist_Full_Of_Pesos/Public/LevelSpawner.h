// Fill out your copyright notice in the Description page of Project Settings.
// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#pragma once // Asegura que este archivo de encabezado solo se incluya una vez durante la compilación.

#include "CoreMinimal.h" // Incluye los componentes esenciales del motor de Unreal.
#include "GameFramework/Actor.h" // Incluye la clase base AActor.
#include "LevelSpawner.generated.h" // Genera el código necesario para la clase ALevelSpawner.
class ABaseLevel; // Declaración anticipada de la clase ABaseLevel.

/**
 * Clase ALevelSpawner que hereda de AActor.
 */
UCLASS() // Macro que indica que esta es una clase de Unreal Engine.
class A_FIST_FULL_OF_PESOS_API ALevelSpawner : public AActor
{
	GENERATED_BODY() // Macro que genera el código estándar necesario para las clases de Unreal Engine.

public:
	// Establece los valores predeterminados para las propiedades de este actor.
	ALevelSpawner();

protected:
	// Llamada cuando el juego comienza o cuando el actor es generado.
	virtual void BeginPlay() override;

public:
	// Llamada cada cuadro.
	virtual void Tick(float DeltaTime) override;

public:
	// Función para generar un nivel, toma un parámetro booleano para indicar si es el primer nivel.
	UFUNCTION()
		void SpawnLevel(bool IsFirst);

	// Función que se llama cuando ocurre una superposición.
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappepedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult);

protected:
	// Puntero al jugador.
	APawn* Player;

	// Propiedades para las clases de niveles editables en el editor.
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseLevel> Level1;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseLevel> Level2;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseLevel> Level3;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseLevel> Level4;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseLevel> Level5;

	// Lista de niveles generados.
	TArray<ABaseLevel*> LevelList;

public:
	// Nivel aleatorio seleccionado.
	int RandomLevel;

	// Ubicación de generación del nivel.
	FVector SpawnLocation = FVector();

	// Rotación de generación del nivel.
	FRotator SpawnRotation = FRotator();

	// Parámetros de generación del actor.
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
};
