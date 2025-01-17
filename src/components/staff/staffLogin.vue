<template>
  <div class="loginBox">
    <div class="box">
      <div>
        <div
          v-if="isLogin"
          style="display: flex; flex-direction: column; align-items: center"
        >
          <img
            :src="lineupLogo"
            alt="lineupLogo"
            class="logo"
            style="margin-top: 1.5rem"
          />
          <div>
            <div class="window">
              {{ window }}
            </div>
          </div>
          <form @submit.prevent="handleLogin">
            <input type="text" placeholder="Staff Name" v-model="staff" />
            <button type="submit" @click="Start">Start</button>
          </form>
          <div style="display: flex; padding: 1rem">
            <span class="switchAccount"> or </span>
            <span
              class="switchAccount"
              style="
                color: #052c65;
                font-weight: 700;
                text-decoration: underline;
                cursor: pointer;
              "
              @click="switchAccount"
            >
              Switch Account
            </span>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import lineupLogo from "@/assets/darkLogo.svg";
  import googleLogo from "@/assets/googleLogo.svg";
  import { supabase } from "@/client/supabase";

  export default {
    name: "loginBox",
    data() {
      return {
        lineupLogo,
        googleLogo,
        isLogin: true,
        regIsVisible: false,
        window: "Window 1",
        authIsVisible: false,
        staff: "",
        code: Array(6).fill(""),
      };
    },
    methods: {
      async Start() {
        const { data, error } = await supabase
          .from("users")
          .select("display_name")
          .eq("display_name", this.staff);

        const { error: insertError } = await supabase
          .from("staff_logs")
          .insert({ window_number: this.window, staff: this.staff, start: "12:11:22", date: new Date()});

        if (data.length === 0) {
          alert("Staff not found");
        } else {
          this.$router.push("/staffhome");
        }
      },
      async switchAccount() {
        await supabase.auth.signOut();
        this.$router.push("/login");
      },
    },
  };
</script>

<style scoped>
  .loginBox {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
    width: 100vw;
  }

  .box {
    display: flex;
    align-items: center;
    flex-direction: column;
    width: 29rem;
    height: 26.1875rem;
    padding: 2rem;
    background-color: white;
    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
    border-radius: 10px;
  }

  .window {
    width: 22.5em;
    height: 2.1875rem;
    background-color: white;
    border: 1px solid #052c65;
    border-radius: 3px;
    margin: -1px;
    margin-top: 0.5rem;
    margin-bottom: 0.5rem;
    display: flex;
    align-items: center;
    justify-content: center;
    color: #052c65;
    font-weight: 700;
  }

  .logRegSwitch.active {
    background-color: #052c65;
    color: white;
  }

  form {
    display: flex;
    align-items: center;
    flex-direction: column;
    gap: 0.5rem;
  }

  input {
    width: 22.5rem;
    height: 3rem;
    padding: 1rem;
    border: 1px solid #ccc;
    border-radius: 4px;
  }

  button[type="submit"] {
    background-color: #052c65;
    width: 5.4375rem;
    height: 3.125rem;
    color: white;
    border: none;
    padding: 0.5rem;
    border-radius: 4px;
    cursor: pointer;
    margin-top: 1rem;
  }

  .numContainer {
    display: flex;
    justify-content: center;
    align-items: center;
    gap: 10px;
    width: 100%;
    margin: 1rem 0 2rem 0;
  }

  .num {
    width: 57px;
    height: 78px;
    box-sizing: border-box;
    border-radius: 20px;
    border: none;
    background-color: #f0f1f5;
    background-position: 10px center;
    background-repeat: no-repeat;
    padding-left: 22px;
    font-size: 30px;
  }

  .verifyButton {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 85%;
    height: 46px;
    border-radius: 10px;
    background-color: #174082;
    font-size: 16px;
    color: #f0f1f5;
    font-weight: 600;
    border: none;
    cursor: pointer;
  }

  .switchAccount {
    font-weight: 400;
    font-size: 0.75rem;
    padding: 0 0.3rem 0 0;
  }
</style>
