#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Coin.generated.h"

UCLASS()
class A_FIST_FULL_OF_PESOS_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Colision con el jugador
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Componente de la moneda
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* CoinMesh;
};