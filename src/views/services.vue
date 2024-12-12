<template>
    <navbar />
    <servicesOffered />
    <licensing />
    <registration />
    <letas />
    <foot />
</template>

<script>
import navbar from '@/components/staff/staffnavbar.vue'
import servicesOffered from '@/components/servicesOffered.vue';
import licensing from '@/components/licensing.vue';
import foot from '@/components/staff/staffFooter.vue';
import registration from '@/components/registration.vue';
import letas from '@/components/letas.vue'

export default {
    components: { navbar, servicesOffered, licensing, registration, letas, foot},
}
</script>

