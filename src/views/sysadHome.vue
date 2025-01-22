<template>
    <navbar />
    <land-page />
    <lineupMinds />
    <foot />
</template>

<script>
import LandPage from '@/components/SysAd/adminlandpage.vue'
import navbar from '@/components/SysAd/adminnavbar.vue'
import lineupMinds from '@/components/lineupMinds.vue'
import foot from '@/components/SysAd/adminfooter.vue'

export default {
  components: { navbar, LandPage, lineupMinds, foot},
}
</script>
