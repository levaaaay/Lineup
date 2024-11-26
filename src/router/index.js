import { createRouter, createWebHistory } from 'vue-router';
import homeView from '@/views/home.vue';
import services from '@/views/services.vue';
import login from '@/views/login.vue';
import schedule from '@/views/schedule.vue';
import ticket from '@/views/ticket.vue';

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
  },
  {
    path: '/schedule',
    name: 'schedule',
    component: schedule
  },
  {
    path: '/ticket',
    name: 'ticket',
    component: ticket
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
