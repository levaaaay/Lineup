<template>
    <navbar />
    <report />
    <foot />
</template>

<script>
import navbar from '@/components/superAdmin/supernavbar.vue'
import foot from '@/components/SysAd/adminfooter.vue'
import report from '@/components/superAdmin/report.vue';

export default {
  components: { navbar, foot, report},
}
</script>
