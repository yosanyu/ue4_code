// Fill out your copyright notice in the Description page of Project Settings.


#include "Elixirs.h"

FElixirs::FElixirs() {

}

bool FElixirs::operator==(const FElixirs& other) const {
	return id == other.id;
}

uint32 GetTypeHash(const FElixirs& other) {
	return uint32(other.id);
}
