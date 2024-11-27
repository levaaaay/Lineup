<template>
    <navbar />
    <land-page />
    <aboutUs />
    <qWithL />
    <lineupMinds />
    <foot />
</template>

<script>
import LandPage from '@/components/SysAd/adminlandpage.vue'
import qWithL from '@/components/qWithL.vue'
import navbar from '@/components/SysAd/adminnavbar.vue'
import AboutUs from '@/components/aboutUs.vue'
import lineupMinds from '@/components/lineupMinds.vue'
import foot from '@/components/SysAd/adminfooter.vue'

export default {
  components: { navbar, LandPage, AboutUs, qWithL, lineupMinds, foot},
}
</script>
