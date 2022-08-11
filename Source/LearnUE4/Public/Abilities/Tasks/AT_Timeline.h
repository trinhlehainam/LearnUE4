// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Components/TimelineComponent.h"
#include "AT_Timeline.generated.h"

/** Signature of function to handle a timeline 'event' */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimelineEventDelegate);

UENUM(BlueprintType)
enum class ETimelineInputExecution : uint8
{
	Play,
	PlayFromStart,
	Stop,
	Reverse,
	ReverseFromEnd,
	SetNewTime
};

/**
 * TODO: Custom UK2Node to provide friendly UI to create UAT_Timeline in Blueprint Graph
 */
UCLASS()
class LEARNUE4_API UAT_Timeline : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnTimelineEventDelegate OnUpdate;

	UPROPERTY(BlueprintAssignable)
	FOnTimelineEventDelegate OnFinished;

	UFUNCTION(BlueprintCallable, meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility"), Category="Ability|Tasks")
	static UAT_Timeline* CreateTimelineTask(UGameplayAbility* OwningAbility);

	/** Start playback of timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void Play();

	/** Start playback of timeline from the start */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void PlayFromStart();

	/** Start playback of timeline in reverse */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void Reverse();

	/** Start playback of timeline in reverse from the end */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void ReverseFromEnd();

	/** Stop playback of timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void Stop();

	/** Get whether this timeline is playing or not. */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	bool IsPlaying() const;

	/** Get whether we are reversing or not */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	bool IsReversing() const;

	/** Jump to a position in the timeline. 
	  * @param bFireEvents If true, event functions that are between current position and new playback position will fire. 
	  * @param bFireUpdate If true, the update output exec will fire after setting the new playback position.
	 */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline", meta=(AdvancedDisplay="bFireUpdate"))
	void SetPlaybackPosition(float NewPosition, bool bFireEvents, bool bFireUpdate = true);

	/** Get the current playback position of the Timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	float GetPlaybackPosition() const;

	/** true means we would loop, false means we should not. */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void SetLooping(bool bNewLooping);

	/** Get whether we are looping or not */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	bool IsLooping() const;

	/** Sets the new play rate for this timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void SetPlayRate(float NewRate);

	/** Get the current play rate for this timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	float GetPlayRate() const;

	/** Set the new playback position time to use */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void SetNewTime(float NewTime);

	/** Get length of the timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	float GetTimelineLength() const;

	/** Set length of the timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void SetTimelineLength(float NewLength);

	/** Sets the length mode of the timeline */
	UFUNCTION(BlueprintCallable, Category="Components|Timeline")
	void SetTimelineLengthMode(ETimelineLengthMode NewLengthMode);

	/** Update a certain float track's curve */
	UFUNCTION(BlueprintCallable, Category = "Components|Timeline")
	void SetFloatCurve(UCurveFloat* NewFloatCurve, FName FloatTrackName);

	/** Update a certain vector track's curve */
	UFUNCTION(BlueprintCallable, Category = "Components|Timeline")
	void SetVectorCurve(UCurveVector* NewVectorCurve, FName VectorTrackName);

	/** Update a certain linear color track's curve */
	UFUNCTION(BlueprintCallable, Category = "Components|Timeline")
	void SetLinearColorCurve(UCurveLinearColor* NewLinearColorCurve, FName LinearColorTrackName);
	
	/** Add a callback event to the timeline */
	void AddEvent(float Time, FOnTimelineEvent EventFunc);
	
	/** Add a vector interpolation to the timeline */
	void AddInterpVector(UCurveVector* VectorCurve, FOnTimelineVector InterpFunc, FName PropertyName = NAME_None, FName TrackName = NAME_None);
	
	/** Add a float interpolation to the timeline */
	void AddInterpFloat(UCurveFloat* FloatCurve, FOnTimelineFloat InterpFunc, FName PropertyName = NAME_None, FName TrackName = NAME_None);

	/** Add a linear color interpolation to the timeline */
	void AddInterpLinearColor(UCurveLinearColor* LinearColorCurve, FOnTimelineLinearColor InterpFunc, FName PropertyName = NAME_None, FName TrackName = NAME_None);
	
	/** Optionally provide an object to automatically update properties on */
	void SetPropertySetObject(UObject* NewPropertySetObject);

	/** Set the delegate to call after each timeline tick */
	void SetTimelinePostUpdateFunc(FOnTimelineEvent NewTimelinePostUpdateFunc);

	/** Set the delegate to call when timeline is finished */
	void SetTimelineFinishedFunc(FOnTimelineEvent NewTimelineFinishedFunc);
	
	/** Set the static delegate to call when timeline is finished */
	void SetTimelineFinishedFunc(FOnTimelineEventStatic NewTimelineFinishedFunc);

	/** Set the delegate to call when timeline is finished */
	void SetDirectionPropertyName(FName DirectionPropertyName);

	/** Get all curves used by the Timeline */
	void GetAllCurves(TSet<UCurveBase*>& InOutCurves) const;

protected:
	virtual void TickTask(float DeltaTime) override;

	FTimeline TheTimeline;
};
