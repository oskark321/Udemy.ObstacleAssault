// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float MemberFloat = 10.0f;

	UPROPERTY(VisibleAnywhere)
	int MemberInt = 15;

	struct VektorTest
	{
		float X;
		float Y;
		float Z;
	};

	FVector ActorLocation;
	UPROPERTY(EditAnywhere)
	FVector IntroVector = FVector(2.44f, 5.31f, 142.0f); //konstruktor FVector aby przypisaæ od razu X Y Z

	FVector CurrentLocation;
	
	/*
	UPROPERTY(EditAnywhere)
	float MoveSpeedX = 0.0f;
	UPROPERTY(EditAnywhere)
	float MoveSpeedY = 0.0f;
	UPROPERTY(EditAnywhere)
	float MoveSpeedZ = 0.0f;
	*/

	int MyTestFunction(float OnlyForTest, float MyNewTestFloat, FString MyTestString);
	void MyMemberFunction(int MyInt);
	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	float GetDistanceMoved();
	void RotateAndBackPlatform(float DeltaTime);

	FVector StartLocation;
	
	UPROPERTY(EditAnywhere)
	FVector PlatformVelocity = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	float MoveDistance = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float DistanceMoved = 0.0f;

	UPROPERTY(EditAnywhere)
	FRotator RotationVelocity = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	FRotator RotationBackVelocity = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	float RotationAngle = 0.0f;

	UPROPERTY(VisibleAnywhere)
	FRotator DistanceRotation;

	FRotator StartRotation;



};
