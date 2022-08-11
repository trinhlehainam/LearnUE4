// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Tasks/AT_Timeline.h"

UAT_Timeline* UAT_Timeline::CreateTimelineTask(UGameplayAbility* OwningAbility)
{
	UAT_Timeline* TaskInstance = NewAbilityTask<UAT_Timeline>(OwningAbility);
	
	return TaskInstance;
}

void UAT_Timeline::Play()
{
	bTickingTask = true;
	TheTimeline.Play();
}

void UAT_Timeline::PlayFromStart()
{
	bTickingTask = true;
	TheTimeline.PlayFromStart();
}

void UAT_Timeline::Reverse()
{
	bTickingTask = true;
	TheTimeline.Reverse();
}

void UAT_Timeline::ReverseFromEnd()
{
	bTickingTask = true;
	TheTimeline.ReverseFromEnd();
}

void UAT_Timeline::Stop()
{
	bTickingTask = false;
	TheTimeline.Stop();
}

bool UAT_Timeline::IsPlaying() const
{
	return TheTimeline.IsPlaying();
}

void UAT_Timeline::AddEvent(float Time, FOnTimelineEvent Event)
{
	TheTimeline.AddEvent(Time, Event);
}

void UAT_Timeline::AddInterpVector(UCurveVector* VectorCurve, FOnTimelineVector InterpFunc, FName PropertyName, FName TrackName)
{
	TheTimeline.AddInterpVector(VectorCurve, InterpFunc, PropertyName, TrackName);
}

void UAT_Timeline::AddInterpFloat(UCurveFloat* FloatCurve, FOnTimelineFloat InterpFunc, FName PropertyName, FName TrackName)
{
	TheTimeline.AddInterpFloat(FloatCurve, InterpFunc, PropertyName, TrackName);
}

void UAT_Timeline::AddInterpLinearColor(UCurveLinearColor* LinearColorCurve, FOnTimelineLinearColor InterpFunc, FName PropertyName, FName TrackName)
{
	TheTimeline.AddInterpLinearColor(LinearColorCurve, InterpFunc, PropertyName, TrackName);
}

void UAT_Timeline::SetPropertySetObject(UObject* NewPropertySetObject)
{
	TheTimeline.SetPropertySetObject(NewPropertySetObject);
}

void UAT_Timeline::SetDirectionPropertyName(FName DirectionPropertyName)
{
	TheTimeline.SetDirectionPropertyName(DirectionPropertyName);
}

void UAT_Timeline::SetPlaybackPosition(float NewPosition, bool bFireEvents, bool bFireUpdate)
{
	TheTimeline.SetPlaybackPosition(NewPosition, bFireEvents, bFireUpdate);
}

float UAT_Timeline::GetPlaybackPosition() const
{
	return TheTimeline.GetPlaybackPosition();
}

void UAT_Timeline::SetLooping(bool bNewLooping)
{
	TheTimeline.SetLooping(bNewLooping);
}

bool UAT_Timeline::IsLooping() const
{
	return TheTimeline.IsLooping();
}

bool UAT_Timeline::IsReversing() const
{
	return TheTimeline.IsReversing();
}

void UAT_Timeline::SetPlayRate(float NewRate)
{
	TheTimeline.SetPlayRate(NewRate);
}

float UAT_Timeline::GetPlayRate() const
{
	return TheTimeline.GetPlayRate();
}

void UAT_Timeline::SetNewTime (float NewTime)
{
	TheTimeline.SetNewTime(NewTime);
}

float UAT_Timeline::GetTimelineLength() const
{
	return TheTimeline.GetTimelineLength();
}

void UAT_Timeline::SetTimelineLength(float NewLength)
{
	return TheTimeline.SetTimelineLength(NewLength);
}

void UAT_Timeline::SetTimelineLengthMode(ETimelineLengthMode NewLengthMode)
{
	TheTimeline.SetTimelineLengthMode(NewLengthMode);
}

void UAT_Timeline::SetFloatCurve(UCurveFloat* NewFloatCurve, FName FloatTrackName)
{
	TheTimeline.SetFloatCurve(NewFloatCurve, FloatTrackName);
}

void UAT_Timeline::SetVectorCurve(UCurveVector* NewVectorCurve, FName VectorTrackName)
{
	TheTimeline.SetVectorCurve(NewVectorCurve, VectorTrackName);
}

void UAT_Timeline::SetLinearColorCurve(UCurveLinearColor* NewLinearColorCurve, FName LinearColorTrackName)
{
	TheTimeline.SetLinearColorCurve(NewLinearColorCurve, LinearColorTrackName);
}

void UAT_Timeline::SetTimelinePostUpdateFunc(FOnTimelineEvent NewTimelinePostUpdateFunc)
{
	TheTimeline.SetTimelinePostUpdateFunc(NewTimelinePostUpdateFunc);
}

void UAT_Timeline::SetTimelineFinishedFunc(FOnTimelineEvent NewTimelineFinishedFunc)
{
	TheTimeline.SetTimelineFinishedFunc(NewTimelineFinishedFunc);
}

void UAT_Timeline::SetTimelineFinishedFunc(FOnTimelineEventStatic NewTimelineFinishedFunc)
{
	TheTimeline.SetTimelineFinishedFunc(NewTimelineFinishedFunc);
}

void UAT_Timeline::GetAllCurves(TSet<class UCurveBase*>& InOutCurves) const
{
	// TheTimeline.GetAllCurves(InOutCurves);
}

void UAT_Timeline::TickTask(float DeltaTime)
{
	TheTimeline.TickTimeline(DeltaTime);
	
	if (!TheTimeline.IsPlaying())
	{
		bTickingTask = false;
	}
}
