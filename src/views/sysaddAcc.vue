<template>
    <navbar />
    <accmanagement />
    <foot />
</template>

<script>
import accmanagement from '@/components/SysAd/accmanagement.vue'
import navbar from '@/components/SysAd/adminnavbar.vue'
import foot from '@/components/SysAd/adminfooter.vue'

export default {
  components: { navbar, accmanagement, foot},
}
</script>
