import { createRouter, createWebHistory } from 'vue-router';
import homeView from '@/views/home.vue';
import services from '@/views/services.vue';
import login from '@/views/login.vue';
import schedule from '@/views/schedule.vue';
import ticket from '@/views/ticket.vue';
import StaffHome from '@/views/staffHome.vue';
import SysadHome from '@/views/sysadHome.vue';
import staffSchedule from '@/views/staffSchedule.vue';
import directing from '@/views/direct.vue';
import SysaddAcc from '@/views/sysaddAcc.vue';
import SysadSchedule from '@/views/sysadSchedule.vue';
import info from '@/views/info.vue';
import staffServicesInfo from '@/components/staff/staffServicesInfo.vue';
import { supabase } from "../client/supabase";

let email;

const routes = [
  {
    path: '/',
    name: 'home',
    component: homeView,
    meta: { requireAuth: true }
  },
  {
    path: '/services',
    name: 'services',
    component: services,
    meta: { requireStaff: true }
  },
  {
    path: '/login',
    name: 'login',
    component: login
  },
  {
    path: '/schedule',
    name: 'schedule',
    component: schedule,
    meta: { requireAuth: true }
  },
  {
    path: '/ticket',
    name: 'ticket',
    component: ticket,
    meta: { requireAuth: true }
  },
  {
    path: '/staffhome',
    name: 'staffhome',
    component: StaffHome,
    meta: { requireStaff: true }

  },
  {
    path: '/sysadhome',
    name: 'sysadhome',
    component: SysadHome,
    meta: { requireAdmin: true }
  },
  {
    path: '/staffschedule',
    name: 'staffschedule',
    component: staffSchedule,
    meta: { requireStaff: true }
  },
  {
    path: '/direct',
    name: 'direct',
    component: directing,
    meta: { directUser: true }
  },
  {
    path: '/account',
    name: 'account',
    component: SysaddAcc,
    meta: { requireAdmin: true }
  },
  {
    path: '/sysadSchedule',
    name: 'sysadSchedule',
    component: SysadSchedule,
    meta: { requireAdmin: true }
  },
  {
    path: '/info',
    name: 'info',
    component: info
  },
  {
    path: '/staffServicesInfo',
    name: 'staffServicesInfo',
    component: staffServicesInfo
  }
];

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
  scrollBehavior(to, from, savedPosition) {
    return { top: 0 };
  }
});

async function directUser(next) {
  const { data: { session } } = await supabase.auth.getSession();
  email = session.user.email;

  const { data, error } = await supabase
  .from("users")
  .select("role") 
  .eq("email", email);
  
  if (data.length === 0) {
        next("/");
  } else {
      if (data[0].role === "staff") {
        next("staffhome");
      } else if (data[0].role === "system admin") {
        next("sysadhome");
      }
    }
}

async function getClient(next) {
  const { data: { session } } = await supabase.auth.getSession();
  if (!session) {
    next("/login");
    return;
  } 
  email = session.user.email;

  const { data, error } = await supabase
  .from("users")
  .select("role") 
  .eq("email", email);

  if (data.length !== 0) {
    if (data[0].role === "staff") {
      next("/staffhome");
    }
  }

  next();
}

async function getStaff(next) {
  const { data: { session } } = await supabase.auth.getSession();
  if (!session) {
    next("/login");
    return;
  } 
  email = session.user.email;

  const { data, error } = await supabase
  .from("users")
  .select("role") 
  .eq("email", email);

  if (data.length === 0) {
    next("/")
  } else {
    if (data[0].role === "staff") {
      next();
    } else if (data[0].role === "system admin") {
      next();
    } 
  }
}

async function getAdmin(next) {
  const { data: { session } } = await supabase.auth.getSession();
  if (!session) {
    next("/login");
    return;
  } 
  email = session.user.email;

  const { data, error } = await supabase
  .from("users")
  .select("role") 
  .eq("email", email);

  if (data.length === 0) {
    next("/")
  } else {
    if (data[0].role === "staff") {
      next("/staffhome");
    } else if (data[0].role === "system admin") {
      next();
    } 
  }
}

router.beforeEach((to, from, next) => {
  if (to.meta.requireAuth) {
    getClient(next);
  }
  else if (to.meta.requireStaff){
    getStaff(next);
  }
  else if (to.meta.directUser) {
    directUser(next);
  }
  else if (to.meta.requireAdmin) {
    getAdmin(next);
  }
  else {
    next();
  }
})

export default router;

