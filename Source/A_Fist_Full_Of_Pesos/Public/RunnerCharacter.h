// Completa tu aviso de copyright en la página de Descripción de la Configuración del Proyecto.

#pragma once // Asegura que este archivo de encabezado solo se incluya una vez durante la compilación.

#include "CoreMinimal.h" // Incluye los componentes esenciales del motor de Unreal.
#include "GameFramework/Character.h" // Incluye la clase base ACharacter.
#include "RunnerCharacter.generated.h" // Genera el código necesario para la clase ARunnerCharacter.

// Declaración de clases y estructuras
class USpringArmComponent; // Declara la clase USpringArmComponent.
class UCameraComponent; // Declara la clase UCameraComponent.
class UInputMappingContext; // Declara la clase UInputMappingContext.
class UInputAction; // Declara la clase UInputAction.
struct FInputActionValue; // Declara la estructura FInputActionValue.

// Declaración de una categoría de log para la clase
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game) // Macro que indica que esta es una clase de Unreal Engine y especifica la configuración del juego.
class A_FIST_FULL_OF_PESOS_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY() // Macro que genera el código estándar necesario para las clases de Unreal Engine.

		// Propiedades visibles en cualquier lugar
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* SideViewCamera; // Cámara lateral.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SideViewCameraBoom;




	///** Boom de la cámara que posiciona la cámara detrás del personaje */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	USpringArmComponent* CameraBoom; // Componente de boom de la cámara.

	///** Cámara de seguimiento */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	UCameraComponent* FollowCamera; // Componente de cámara de seguimiento.

	///** Contexto de mapeo de entrada */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext; // Contexto de mapeo de entrada predeterminado.

	///** Acción de entrada para saltar */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* JumpAction; // Acción de entrada para saltar.

	///** Acción de entrada para moverse */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* MoveAction; // Acción de entrada para moverse.

	///** Acción de entrada para mirar */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LookAction; // Acción de entrada para mirar.

	///** Acción de entrada para interactuar */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//	UInputAction* InteractAction; // Acción de entrada para interactuar.

public:
	// Establece los valores predeterminados para las propiedades de este personaje.
	ARunnerCharacter();

protected:
	// Llamada cuando el juego comienza o cuando el personaje es generado.
	virtual void BeginPlay() override;


public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//	TSubclassOf<UUserWidget> BP_UI_Class;
	// Contador de monedas
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
		int Coins;

	// Método para agregar monedas
	UFUNCTION(BlueprintCallable, Category = "Player")
		void AddCoins(int Amount);

	// Variable para almacenar la distancia recorrida
	float DistanceTraveled;

	// Método para actualizar la distancia recorrida
	void UpdateDistanceTraveled(float DeltaTime);


	// Llamada cada cuadro.
	virtual void Tick(float DeltaTime) override;

	// Llamada para vincular funcionalidades a la entrada del jugador.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Llamada para la entrada de movimiento */
	void Move(const FInputActionValue& Value);

	/** Llamada para la entrada de mirar */
	//void Look(const FInputActionValue& Value);

	/** Llamada para la entrada de interactuar */
	//void Interact(const FInputActionValue& Value);
	//void MoveRight(float value);

public:
	// Obtiene el componente de la cámara lateral.
	class UCameraComponent* GetSideViewCameraComponent() const
	{
		return SideViewCamera;
	}

	// Reinicia el nivel.
	void RestartLevel();

	// Llamada cuando ocurre una superposición.
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappepedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult);

private:
	float zPosition; // Posición en el eje Z.
	FVector tempPosition = FVector(); // Posición temporal.
	FRotator tempRotation = FRotator();
	bool CanMove; // Indica si el personaje puede moverse.
};
