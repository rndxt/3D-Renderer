#ifndef OBSERVER_H
#define OBSERVER_H

#include <Observer.h>

namespace App {

using ByValue = NSLibrary::CByValue;

template <typename T>
using Observable = NSLibrary::CObservable<T>;

template <typename T>
using ObservableByValue = NSLibrary::CObservable<T, ByValue>;

template <typename T>
using ObservableData = NSLibrary::CObservableData<T>;

template <typename T>
using Observer = NSLibrary::CObserver<T>;

template <typename T>
using ObserverByValue = NSLibrary::CObserver<T, ByValue>;

template <typename T>
using ColdObserver = NSLibrary::CColdInput<T>;

template <typename T>
using HotObserver = NSLibrary::CHotInput<T>;

template <typename T>
using HotObserverByValue = NSLibrary::CHotInput<T, ByValue>;

} // namespace App

#endif // OBSERVER_H
