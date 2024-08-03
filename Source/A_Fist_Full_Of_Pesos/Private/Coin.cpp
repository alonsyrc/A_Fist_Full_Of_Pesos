#include "Coin.h"
#include "RunnerCharacter.h"

ACoin::ACoin()
{
	// Inicializa la moneda
	PrimaryActorTick.bCanEverTick = true;

	// Crea el componente de la moneda
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	RootComponent = CoinMesh;

	// Establece la colisión
	CoinMesh->SetCollisionProfileName("Coin");
	CoinMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ARunnerCharacter* RunnerCharacter = Cast<ARunnerCharacter>(OtherActor); // Intenta convertir OtherActor a AWallSpike.
		// Si colisiona con un spike o una pared con espinas
		if (RunnerCharacter)
		{
			RunnerCharacter->AddCoins(1); // Asumiendo que tienes un método AddCoins en tu clase ARunnerCharacter
			// Destruye la moneda
			Destroy();
		}
	}
}