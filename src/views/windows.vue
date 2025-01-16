<template>
    <navbar />
    <windows />
    <foot />
</template>

<script>
import navbar from '@/components/SysAd/adminnavbar.vue'
import foot from '@/components/SysAd/adminfooter.vue'
import windows from '@/components/SysAd/adminWindows.vue';

export default {
  components: { navbar, foot, windows},
}
</script>
