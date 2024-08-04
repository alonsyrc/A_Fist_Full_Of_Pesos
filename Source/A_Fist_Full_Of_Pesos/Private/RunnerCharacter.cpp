#include "RunnerCharacter.h" // Incluye la definición de la clase ARunnerCharacter.
#include "RunnerCharacter.h"
#include "Components/CapsuleComponent.h" // Incluye la clase UCapsuleComponent.
#include "Camera/CameraComponent.h" // Incluye la clase UCameraComponent.
#include "GameFramework/SpringArmComponent.h" // Incluye la clase USpringArmComponent.
#include "GameFramework/CharacterMovementComponent.h" // Incluye la clase UCharacterMovementComponent.
#include "GameFramework/Controller.h" // Incluye la clase AController.
#include "EnhancedInputComponent.h" // Incluye la clase UEnhancedInputComponent.
#include "EnhancedInputSubsystems.h" // Incluye los subsistemas de entrada mejorada.
#include "InputActionValue.h" // Incluye la estructura FInputActionValue.
#include <WallSpike.h> // Incluye la clase AWallSpike.
#include <Spikes.h> // Incluye la clase ASpikes.
#include <Engine.h> // Incluye la clase UEngine.
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "CustomWidget.h"

// Establece valores predeterminados
ARunnerCharacter::ARunnerCharacter()
{
    // Configura este personaje para llamar a Tick() cada cuadro. Puedes desactivar esto para mejorar el rendimiento si no lo necesitas.
    PrimaryActorTick.bCanEverTick = true;
    // Inicializa el tamaño del cápsula de colisión.
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    // Configura la respuesta de colisión.
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

    // Configura la rotación del controlador.
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // Crea el Spring Arm para la cámara lateral.
    SideViewCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SideViewCameraBoom"));
    SideViewCameraBoom->SetupAttachment(RootComponent); // Adjunta el Spring Arm al Root Component del personaje
    SideViewCameraBoom->TargetArmLength = 500.0f; // La distancia de la cámara al personaje.
    SideViewCameraBoom->bUsePawnControlRotation = false; // La cámara no rota según el controlador del Pawn.
    SideViewCameraBoom->SetRelativeRotation(FRotator(-20.0f, -90.0f, 0.0f)); // Ajusta la rotación del Spring Arm.

    // Crea la cámara lateral.
    SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCamera->SetupAttachment(SideViewCameraBoom, USpringArmComponent::SocketName); // Adjunta la cámara al final del Spring Arm.
    SideViewCamera->bUsePawnControlRotation = false; // La cámara no rota según el controlador del Pawn.

    // Configura el movimiento del personaje.
    GetCharacterMovement()->bOrientRotationToMovement = false; // No orienta la rotación al movimiento.
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
    GetCharacterMovement()->GravityScale = 2.0f;
    GetCharacterMovement()->AirControl = 0.8f;
    GetCharacterMovement()->JumpZVelocity = 1050.0f;
    GetCharacterMovement()->GroundFriction = 3.0f;
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->MaxFlySpeed = 650.0f;

    // Configura la posición temporal y la posición en Z.
    tempPosition = GetActorLocation();
}

// Llamado cuando el juego comienza o cuando el personaje es generado
void ARunnerCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Crea una instancia del widget personalizado
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), BP_UI_Ref);

    // Agrega el widget al viewport
    if (Widget)
    {
        Widget->AddToViewport();

        // Encuentra el TextBlock en el widget
        TextBlockDistancia = Cast<UTextBlock>(Widget->GetWidgetFromName("TextBlockDistancia"));
        TextBlockPesos = Cast<UTextBlock>(Widget->GetWidgetFromName("TextBlockPesos"));

        // Verifica si el TextBlock fue encontrado
        if (TextBlockDistancia)
        {
            // Establece el texto del TextBlock
            TextBlockDistancia->SetText(FText::FromString("Distancia"));
        }
        if (TextBlockPesos)
        {
            // Establece el texto del TextBlock
            TextBlockPesos->SetText(FText::FromString("0"));
        }
    }

    // Añade un evento de superposición.
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunnerCharacter::OnOverlapBegin);
    CanMove = true;

    // Añadir contexto de mapeo de entrada.
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

// Llamado cada cuadro
void ARunnerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Actualiza la distancia recorrida
    UpdateDistanceTraveled(DeltaTime);

    // Comprueba si la posición Z del personaje es -200
    if (GetActorLocation().Z <= -20.0f)
    {
        // Reproduce el sonido de reinicio  
        ResetSound(RestartSound);
    }
    if (GetActorLocation().Z <= -200.0f)
    {
        DelayedRestartLevel(); // Llama a la función RestartLevel
    }
}

void ARunnerCharacter::ResetSound(USoundBase* sound)
{
    if (sound != nullptr) // Verifica si el sonido no es nulo
    {
        UAudioComponent* AudioComponent = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));
        if (AudioComponent)
        {
            if (!AudioComponent->IsPlaying()) // Verifica si el componente de audio no está reproduciendo un sonido
            {
                FString soundName = sound->GetName(); // Obtiene el nombre del sonido
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Sonido: %s"), *soundName));
                AudioComponent->SetSound(sound);
                AudioComponent->Play();
            }
            else
            {
                // Maneja el caso en el que el componente de audio ya está reproduciendo un sonido
                UE_LOG(LogTemp, Warning, TEXT("Sonido ya está reproduciéndose"));
            }
        }
    }
    else
    {
        // Maneja el caso en el que el sonido es nulo
        UE_LOG(LogTemp, Warning, TEXT("Sonido nulo"));
    }
}

// Llamado para vincular funcionalidades a la entrada del jugador
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Vincula las acciones de entrada mejorada.
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Saltar
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARunnerCharacter::PlayJumpSound);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Mover
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::Move);
    }
}

// Función de movimiento
void ARunnerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>(); // Obtiene el vector de movimiento.

    if (Controller != nullptr)
    {
        if (CanMove)
        {
            // Obtiene la rotación del controlador.
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);

            // Obtiene el vector hacia adelante basado en la rotación del controlador.
            const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

            // Obtiene el vector hacia la derecha basado en la rotación del controlador.
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

            // Añade el movimiento hacia adelante y hacia atrás.
            AddMovementInput(RightDirection, MovementVector.Y);

            // Añade el movimiento lateral.
            AddMovementInput(ForwardDirection, MovementVector.X);
        }
    }
}

// Reinicia el nivel
void ARunnerCharacter::DelayedRestartLevel()
{
    // Establece un temporizador para reiniciar el nivel después de 2 segundos
    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::RestartLevelDelayed, 2.0f, false);
}

void ARunnerCharacter::RestartLevel()
{
    ResetSound(RestartSound);
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName())); // Reinicia el nivel actual.
}

// Función que reinicia el nivel después del delay
void ARunnerCharacter::RestartLevelDelayed()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName())); // Reinicia el nivel actual.
}

// Maneja las superposiciones
void ARunnerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor != nullptr)
    {
        AWallSpike* WallSpike = Cast<AWallSpike>(OtherActor); // Intenta convertir OtherActor a AWallSpike.
        ASpikes* Spike = Cast<ASpikes>(OtherActor); // Intenta convertir OtherActor a ASpikes.

        // Si colisiona con un spike o una pared con espinas
        if (WallSpike || Spike)
        {
            GetMesh()->Deactivate(); // Desactiva el modelo del personaje.
            GetMesh()->SetVisibility(false); // Hace invisible el modelo del personaje.
            CanMove = false; // Deshabilita el movimiento.

            // Establece un temporizador para reiniciar el nivel después de 2 segundos.
            FTimerHandle UnusedHandle;
            GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::RestartLevel, 2.0f, false);
        }
    }
}

void ARunnerCharacter::AddCoins(int Amount)
{
    Coins += Amount;

    if (TextBlockPesos)
    {
        // Establece el texto del TextBlock
        TextBlockPesos->SetText(FText::FromString(FString::Printf(TEXT("%d"), Coins)));
    }

    // Reproduce el sonido de coin
    ResetSound(CoinSound);
    // Muestra un mensaje en pantalla
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Coins: %d"), Coins));
}

void ARunnerCharacter::PlayJumpSound(const FInputActionValue& Value)
{
    // Obtiene el componente de audio
    UAudioComponent* AudioComponent = Cast<UAudioComponent>(GetComponentByClass(UAudioComponent::StaticClass()));

    if (AudioComponent)
    {
        FString soundName = JumpSound->GetName(); // Obtiene el nombre del sonido
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Sonido: %s"), *soundName));
        AudioComponent->SetSound(JumpSound);
        // Reproduce el sonido
        AudioComponent->Play();
    }
}

void ARunnerCharacter::UpdateDistanceTraveled(float DeltaTime)
{
    // Calcula la velocidad del personaje
    FVector Velocity = GetVelocity();

    // Verifica si el personaje se está moviendo hacia adelante o hacia atrás
    if (Velocity.Y > 0) // Movimiento hacia adelante
    {
        // Calcula la distancia recorrida en este frame
        float DistanceThisFrame = Velocity.Size() * DeltaTime;

        // Actualiza la distancia total recorrida
        DistanceTraveled += DistanceThisFrame;
    }
    else if (Velocity.Y < 0) // Movimiento hacia atrás
    {
        // Calcula la distancia recorrida en este frame
        float DistanceThisFrame = Velocity.Size() * DeltaTime;

        // Resta la distancia recorrida de la distancia total
        DistanceTraveled -= DistanceThisFrame;
    }

    if (TextBlockDistancia)
    {
        // Establece el texto del TextBlock
        TextBlockDistancia->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::FloorToInt(DistanceTraveled / 100.0f))));
    }
}