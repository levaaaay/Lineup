<template>
    <navbar />
    <LicensingInfo />
    <RegistrationInfo />
    <LetasInfo />
    <foot />
</template>

<script>
import navbar from '@/components/staff/staffnavbar.vue'
import foot from '@/components/staff/staffFooter.vue';
import LicensingInfo from '@/components/staff/licensingInfo.vue';
import RegistrationInfo from '@/components/staff/registrationInfo.vue';
import LetasInfo from '@/components/staff/letasInfo.vue';

export default {
    components: { navbar, LicensingInfo, RegistrationInfo, LetasInfo, foot },
};
</script>
