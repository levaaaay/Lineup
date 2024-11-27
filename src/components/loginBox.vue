<template>
  <div class="loginBox">
    <div class="box">
      <div class="container">
        <img :src="lineupLogo" class="lineupLogo" />
      </div>
      <div v-if="loginIsVisible">
        <div class="container">
          <p class="loginText">Log in with Email</p>
        </div>
        <div class="container">
          <form>
            <input type="email" required placeholder="Email" class="email" v-model="email" />
            <input type="password" required placeholder="Password" class="password" v-model="password" />
          </form>
        </div>
        <div class="container">
          <button class="button" @click="login" id="getStarted">
            Get Started
          </button>
        </div>
        <div class="container">
          <div class="signIn">or sign in with</div>
        </div>
        <div class="container">
          <img :src="googleLogo" class="googleLogo" @click="signInWithGoogle" />
        </div>
      </div>
      <div v-if="authIsVisible">
        <div class="container" style="flex-direction: column;">
            <p>Enter the 6-digit code sent to your email.</p>
          <div class="numContainer">
            <div class="numbox" v-for="(digit, index) in code" :key="index">
              <form>
                <input type="text" required class="num" maxlength="1" inputmode="numeric" @input="validateInput($event)"
                  v-model="code[index]" />
              </form>
            </div>
          </div>
          <button class="verifyButton" @click="authenticate">Verify</button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import lineupLogo from "@/assets/lineupLogo.svg";
import googleLogo from "@/assets/googleLogo.svg";
import lock from "@/assets/lock.svg";
import { supabase } from "../client/supabase";

export default {
  name: "loginBox",
  data() {
    return {
      lineupLogo,
      googleLogo,
      lock,
      email: "",
      password: "",
      code: Array(6).fill(""),
      loginIsVisible: true,
      authIsVisible: false,
    };
  },
  methods: {
    async login() {
      const { data, error } = await supabase.auth.signInWithPassword({
        email: this.email,
        password: this.password,
      });
      if (error) {
        alert("Invalid username or password.");
        console.log(await supabase.auth.getSession());
      } else {
        this.loginIsVisible = !this.loginIsVisible;
        this.authIsVisible = !this.authIsVisible;
        const { data, error } = await supabase.auth.signInWithOtp({
          email: this.email,
          options: {
            // set this to false if you do not want the user to be automatically signed up
            shouldCreateUser: false,
          },
        });
      }
    },
    async signInWithGoogle() {
      const { data, error } = await supabase.auth.signInWithOAuth({
        provider: "google",
      });
      if (error) {
        console.log(error);
      }
    },

    async authenticate() {
      const {
        data: { session },
        error,
      } = await supabase.auth.verifyOtp({
        email: this.email,
        token: this.code.join(""),
        type: "email",
      });
      if (error) {
        console.log(error);
        alert("Invalid Code!");
      } else {
        console.log(session);
        this.$router.push("staffhome");
      }
    },
    validateInput(event) {
      const input = event.target;
      if (!/^\d*$/.test(input.value)) {
        input.value = "";
      }
    },
  },
};
</script>

<style scoped>
.loginBox {
  display: flex;
  align-items: center;
  justify-content: center;
  min-height: 100vh;
  margin: 0;
}

.box {
  width: 29rem;
  height: 28.25rem;
  background-color: #FFFFFF;
  border-radius: 15px;
  box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.3);
}


.lineupLogo {
  width: 7.875rem;
  height: 4.375rem;
  margin: 3rem 0 0 0;
}

.loginText {
  color: #212263;
  font-size: 1rem;
  font-weight: 700;
}

.email,
.password {
  width: 85%;
  height: 2.5rem;
  box-sizing: border-box;
  border-radius: 10px;
  font-size: 1rem;
  background-color: #f0f1f5;
  border: none;
  background-position: 10px center;
  background-repeat: no-repeat;
  margin-left: 2rem;
  margin-bottom: 0.75rem;
  padding-left: 2.18rem;
}

.email {
  background-image: url("@/assets/emailLogo.svg");
}

.password {
  background-image: url("@/assets/lock.svg");
}

::placeholder {
  color: #bfc6d4;
  font-weight: 300;
}

.button {
  display: flex;
  justify-content: center;
  align-items: center;
  border-radius: 10px;
  background-color: #052C65;
  font-size: 1rem;
  color: #f0f1f5;
  font-weight: 600;
  border: none;
  cursor: pointer;
}

.button:hover {
  background-color: #084298;
}

.verifyButton {
  display: flex;
  justify-content: center;
  align-items: center;
  width: 85%;
  height: 2.875rem;
  border-radius: 10px;
  background-color: #174082;
  font-size: 1rem;
  color: #f0f1f5;
  font-weight: 600;
  border: none;
  cursor: pointer;
}

#getStarted {
  width: 9.625rem;
  height: 3.9rem;
  margin-top: 1rem;
}

.signIn {
  color: #212631;
  font-size: 0.9375rem;
  margin-top: 0.625rem;
}

.googleLogo {
  margin: 5px 0 20px 0;
  cursor: pointer;
}

.numContainer {
  display: flex;
  justify-content: center;
  align-items: center;
  gap: 0.625rem;
  margin-top: -2.8125rem;
  width: 100%;
}

.num {
  width: 3.5625rem;
  height: 4.875rem;
  box-sizing: border-box;
  border-radius: 20px;
  border: none;
  background-color: #f0f1f5;
  background-position: 10px center;
  background-repeat: no-repeat;
  padding-left: 1.375rem;
  font-size: 1.875rem;
}
</style>
