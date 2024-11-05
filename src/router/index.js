import { createRouter, createWebHistory } from 'vue-router';
import homeView from '@/views/home.vue';
import services from '@/views/services.vue';
import login from '@/views/login.vue';

const routes = [
  {
    path: '/',
    name: 'home',
    component: homeView
  },
  {
    path: '/services',
    name: 'services',
    component: services
  },
  {
    path: '/login',
    name: 'login',
    component: login
  }
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
  scrollBehavior(to, from, savedPosition) {
    return { top: 0 };
  }
});

export default router;
