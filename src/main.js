import { createApp } from 'vue'
import App from './App.vue'
import './assets/global.css'
import router from './router'
import 'bootstrap/dist/css/bootstrap.css'
import bootstrap from 'bootstrap/dist/js/bootstrap.js'

createApp(App).use(router, bootstrap).mount('#app')
