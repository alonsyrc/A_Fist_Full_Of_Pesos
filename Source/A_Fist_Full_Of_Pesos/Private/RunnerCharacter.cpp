// Completa tu aviso de copyright en la p�gina de Descripci�n de la Configuraci�n del Proyecto.

#include "RunnerCharacter.h" // Incluye la definici�n de la clase ARunnerCharacter.

#include "Components/CapsuleComponent.h" // Incluye la clase UCapsuleComponent.
#include "Camera/CameraComponent.h" // Incluye la clase UCameraComponent.
#include "GameFramework/CharacterMovementComponent.h" // Incluye la clase UCharacterMovementComponent.
#include "GameFramework/Controller.h" // Incluye la clase AController.
#include "EnhancedInputComponent.h" // Incluye la clase UEnhancedInputComponent.
#include "EnhancedInputSubsystems.h" // Incluye los subsistemas de entrada mejorada.
#include "InputActionValue.h" // Incluye la estructura FInputActionValue.
#include <WallSpike.h> // Incluye la clase AWallSpike.
#include <Spikes.h> // Incluye la clase ASpikes.
#include <Engine.h> // Incluye la clase UEngine.

// Establece valores predeterminados
ARunnerCharacter::ARunnerCharacter()
{
    // Configura este personaje para llamar a Tick() cada cuadro. Puedes desactivar esto para mejorar el rendimiento si no lo necesitas.
    PrimaryActorTick.bCanEverTick = true;

    // Inicializa el tama�o del c�psula de colisi�n.
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

    // Configura la respuesta de colisi�n.
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

    // Configura la rotaci�n del controlador.
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    // Crea la c�mara lateral.
    SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCamera->bUsePawnControlRotation = false;

    // Configura el movimiento del personaje.
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
    GetCharacterMovement()->GravityScale = 2.0f;
    GetCharacterMovement()->AirControl = 0.8f;
    GetCharacterMovement()->JumpZVelocity = 1000.0f;
    GetCharacterMovement()->GroundFriction = 3.0f;
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->MaxFlySpeed = 600.0f;

    // Configura la posici�n temporal y la posici�n en Z.
    tempPosition = GetActorLocation();
    zPosition = tempPosition.Z + 300.0f;
}

// Llamado cuando el juego comienza o cuando el personaje es generado
void ARunnerCharacter::BeginPlay()
{
    Super::BeginPlay();

    // A�ade un evento de superposici�n.
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunnerCharacter::OnOverlapBegin);
    CanMove = true;

    // Mensaje de depuraci�n en pantalla.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OA"));

    // A�adir contexto de mapeo de entrada.
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

    // Actualiza la posici�n de la c�mara lateral.
    tempPosition = GetActorLocation();
    tempPosition.X -= 850.0f; // Mueve la c�mara hacia la izquierda.
    tempPosition.Z = zPosition; // Mantiene la posici�n en Z.

    SideViewCamera->SetWorldLocation(tempPosition); // Establece la nueva ubicaci�n de la c�mara.
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
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Mover
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::Move);
    }
}

// Funci�n de movimiento
void ARunnerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>(); // Obtiene el vector de movimiento.

    if (Controller != nullptr)
    {
        // Mensaje de depuraci�n en pantalla.
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Entra Aqui"));

        if (CanMove)
        {
            // Mensaje de depuraci�n en pantalla.
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Entra Aqui tambien"));

            // Obtiene la rotaci�n del controlador.
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);

            // Obtiene el vector hacia adelante.
            const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

            // Obtiene el vector hacia la derecha.
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

            // A�ade el movimiento.
            AddMovementInput(ForwardDirection, MovementVector.Y);
            AddMovementInput(RightDirection, MovementVector.X);
        }
    }
}

// Reinicia el nivel
void ARunnerCharacter::RestartLevel()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName())); // Reinicia el nivel actual.
}

// Maneja las superposiciones
void ARunnerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappepedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult)
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

            // Establece un temporizador para reiniciar el nivel despu�s de 2 segundos.
            FTimerHandle UnusedHandle;
            GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::RestartLevel, 2.0f, false);
        }
    }
}
