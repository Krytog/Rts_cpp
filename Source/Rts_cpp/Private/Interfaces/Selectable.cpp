// Fill out your copyright notice in the Description page of Project Settings.


#include "Selectable.h"

// Add default functionality here for any ISelectible functions that are not pure virtual.

ISelectable::FDestroyedEvent& ISelectable::OnDestroyed()
{
	return DestroyedEvent;
}

void ISelectable::NotifyThatDestroyed()
{
	DestroyedEvent.Broadcast(this);
}
