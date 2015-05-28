//
// Copyright (c) 2015, Microsoft Corporation
// 
// Permission to use, copy, modify, and/or distribute this software for any 
// purpose with or without fee is hereby granted, provided that the above 
// copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
// IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//

#pragma once

#include "Locks.h"
#include "OnboardingAccessPoint.h"
#include "OnboardingConfig.h"

namespace OnBoardee
{
    public ref class OnboardingService sealed : org::alljoyn::IOnboardingService
    {
    public:
        OnboardingService();
        virtual ~OnboardingService();

        void Initialize();
        void Shutdown();

        // AllJoyn on boarding services

        // methods
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingConfigureWifiResult^>^ ConfigureWifiAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info, _In_ Platform::String^ interfaceMemberSSID, _In_ Platform::String^ interfaceMemberPassphrase, _In_ int16 interfaceMemberAuthType);
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingConnectResult^>^ ConnectAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingOffboardResult^>^ OffboardAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingGetScanInfoResult^>^ GetScanInfoAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

        // properties
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingGetVersionResult^>^ GetVersionAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingGetStateResult^>^ GetStateAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);
        virtual Windows::Foundation::IAsyncOperation<org::alljoyn::OnboardingGetLastErrorResult^>^ GetLastErrorAsync(Windows::Devices::AllJoyn::AllJoynMessageInfo^ info);

    private:
        Windows::Devices::WiFi::WiFiAdapter^ GetWiFiAdapter();
        void ConnectToNetwork(Windows::Devices::WiFi::WiFiAvailableNetwork^ network);

        org::alljoyn::OnboardingProducer^ m_producer;
        Windows::Devices::AllJoyn::AllJoynBusAttachment^ m_busAttachment;
        OnboardingConfig m_config;

        OnboardingAccessPoint^ m_accessPoint;

        Windows::Devices::WiFi::WiFiAdapter^ m_wifiAdapter;
        Platform::String^ m_personalSSID;
        Platform::String^ m_personalPassphrase;

        // As defined here https://allseenalliance.org/developers/learn/base-services/onboarding/interface-14-02
        enum AuthType
        {
            WPA2_AUTO = -3,
            WPA_AUTO = -2,
            Any = -1,
            Open = 0,
            WEP = 1,
            WPA_TKIP = 2,
            WPA_CCMP = 3,
            WPA2_TKIP = 4,
            WPA5_CCMP = 5,
            WPS = 6
        } m_authType;
        
        enum OnBoardingState
        {
            NotConfigured = 0,
            ConfiguredNotValidated = 1,
            ConfiguredValidating = 2,
            ConfiguredValidated = 3,
            ConfiguredError = 4,
            ConfiguredRetry = 5
        } m_state;
        
        enum OnBoardingError
        {
            Validated = 0,
            Unreachable = 1,
            UnsupportedProtocol = 2,
            Unauthorized = 3,
            ErrorMessage = 4
        } m_error;

        Platform::String^ m_errorMessage;
        CSLock m_stateLock;
    };
}

