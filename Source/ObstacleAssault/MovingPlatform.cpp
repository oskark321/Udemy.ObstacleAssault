// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	/*
	int NumberOfApples = 10;
	int NumberOfOranges = 7;
	UE_LOG(LogTemp, Warning, TEXT("Number of apples: %d, and oranges: %d"), NumberOfApples, NumberOfOranges); //mo¿e byæ %i dla integer a %d jest ogólnie dla liczb cza³kowitych

	float PiNumber = 3.14159f;
	UE_LOG(LogTemp, Warning, TEXT("Pi Number: %f"), PiNumber);

	FString MyName = "Oskar";
	UE_LOG(LogTemp, Warning, TEXT("My Name is %s"), *MyName);

	int MyValue = -5 * -2;
	UE_LOG(LogTemp, Warning, TEXT("Value is %d"), MyValue);

	UE_LOG(LogTemp, Warning, TEXT("Member Float is %f"), MemberFloat);
	UE_LOG(LogTemp, Warning, TEXT("Member Int is %d"), MemberInt);

	VektorTest MyVector;
	MyVector.X = 10.4f;
	UE_LOG(LogTemp, Warning, TEXT("Vector Test X is %f"), MyVector.X);
	*/

	//ActorLocation = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Actor Location is X: %f, Y: %f, Z: %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z);

	//UE_LOG(LogTemp, Warning, TEXT("Konstruktor FVector is X: %f, Y: %f, Z: %f"), IntroVector.X, IntroVector.Y, IntroVector.Z);

	ActorLocation = FVector(ActorLocation.X + IntroVector.X, ActorLocation.Y+ IntroVector.Y, ActorLocation.Z + IntroVector.Z);
	//SetActorLocation(ActorLocation);
	//UE_LOG(LogTemp, Warning, TEXT("New Actor Location is X: %f, Y: %f, Z: %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z);

	FString ActorName = GetName();
	int ReturnValue = MyTestFunction(12.0f, 51.458f, ActorName);

	//UE_LOG(LogTemp, Warning, TEXT("My return value is %d"), ReturnValue);

	MyMemberFunction(17);

	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//ActorLocation.X = ActorLocation.X + 1.0f;
	//SetActorLocation(ActorLocation);
	//UE_LOG(LogTemp, Warning, TEXT("New Actor Location is X: %f, Y: %f, Z: %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
	RotateAndBackPlatform(DeltaTime);

}
//S2 L29 30
int AMovingPlatform::MyTestFunction(float OnlyForTest, float MyNewTestFloat, FString MyTestString)
{
	//UE_LOG(LogTemp, Warning, TEXT("My Test Function and test float is %f and %f"), OnlyForTest, MyNewTestFloat);
	//UE_LOG(LogTemp, Warning, TEXT("My String is a name of Actor: %s"), *MyTestString);

	return 13;
}
//S2 L31
void AMovingPlatform::MyMemberFunction(int MyInt)
{
	//UE_LOG(LogTemp, Warning, TEXT("My Member Function and MyInt is %d"), MyInt);
}
//S2 L31
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	/* przeniesione do else i funkcji GetDistanceMoved
	//S2 L38
	CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	SetActorLocation(CurrentLocation);
	S2 L34
	DistanceMoved = FVector::Dist(StartLocation, CurrentLocation); przekszta³camy to w funkcjê return
	*/

	DistanceMoved = GetDistanceMoved();

	
	if (DistanceMoved >= MoveDistance) //tutaj sprawdzamy czy platforma nie polecia³a zaa dalego jak chcemy
	{
		//S2 L37
		FVector DirectionPlatform = PlatformVelocity.GetSafeNormal(); //zwraca nam kierunek wektora
		FVector NewStartLocation = StartLocation + (DirectionPlatform * MoveDistance); //ustawiamy now¹ lokalizacjê punkt pocz¹tkowy to stara lokalizacja startowa
		//dodajemy kierunek ruchu pomno¿ony przez odleg³oœæ ruchu
		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;

		//S2 L35
		PlatformVelocity = -PlatformVelocity; //tutaj odwracamy kierunek ruchu platformy
		//StartLocation = CurrentLocation; //dziêki temu zmienia nam siê pocz¹tkowa lokalizacja i platforma wraca na sowje miejsce bo odleg³oœæ leci od nowa

		float Overshoot = DistanceMoved - MoveDistance; //S2 L36
		//UE_LOG(LogTemp, Warning, TEXT("Overshoot actor: %s is %f"), *GetName(), Overshoot);
	}
	else
	{
		CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}


}
//S2 L31
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Test Rotate Platform"));

	//S2 L39 rotacja platformy
	FRotator RotationToAdd = RotationVelocity * DeltaTime;
	AddActorLocalRotation(RotationToAdd);
	
}
//S2 L38
float AMovingPlatform::GetDistanceMoved()
{
	
	//S2 L34 sprawdza jak daleko platforma siê przesune³a
	return FVector::Dist(StartLocation, GetActorLocation());

}

void AMovingPlatform::RotateAndBackPlatform(float DeltaTime)
{
	//to ju¿ moje aby rotacja obruci³a siê kawa³ek i wróci³a
	DistanceRotation = GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), DistanceRotation.Roll, DistanceRotation.Pitch, DistanceRotation.Yaw);

	if (DistanceRotation.Roll >= RotationAngle || DistanceRotation.Pitch >= RotationAngle || DistanceRotation.Yaw >= RotationAngle)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), DistanceRotation.Roll, DistanceRotation.Pitch, DistanceRotation.Yaw);
		FRotator RotationToAdd = RotationBackVelocity * DeltaTime; //tutaj mno¿my rotacjê razy Deltê aby dzia³a³o dobrze z FPS
		AddActorLocalRotation(RotationToAdd);
		
	}
	else
	{
		FRotator RotationToAdd = RotationBackVelocity * DeltaTime; //tutaj mno¿my rotacjê razy Deltê aby dzia³a³o dobrze z FPS
		AddActorLocalRotation(RotationToAdd);
		//UE_LOG(LogTemp, Warning, TEXT("Else"));
	}

}