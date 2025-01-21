<template>
    <div class="layout">
      <navbar />
      <div class="content">
        <SuperLandPage />
      </div>
      <foot class="footer" />
    </div>
  </template>
  
  <script>
  import navbar from '@/components/superAdmin/supernavbar.vue'
  import foot from '@/components/SysAd/adminfooter.vue'
  import SuperLandPage from '@/components/superAdmin/superLandPage.vue'
  
  export default {
    components: { navbar, foot, SuperLandPage },
  }
  </script>
  
  <style scoped>
  .layout {
    display: flex;
    flex-direction: column;
    min-height: 100vh; 
  }
  
  .content {
    flex: 1;
    display: flex;
    flex-direction: column;
    background-color: #dee2e6;
  }
  
  .footer {
    background: #031633;
    color: #ffffff;
    text-align: center;
  }
  </style>
  