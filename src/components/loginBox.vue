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
            <button
              class="logRegSwitch"
              :class="{ active: isLogin }"
              @click="showLogin"
            >
              Login
            </button>
            <button
              class="logRegSwitch"
              :class="{ active: !isLogin }"
              @click="showRegister"
            >
              Register
            </button>
          </div>
          <form @submit.prevent="handleLogin">
            <input type="email" placeholder="Email" v-model="loginEmail" />
            <input
              type="password"
              placeholder="Password"
              v-model="loginPassword"
            />
            <button type="submit">Login</button>
          </form>
          <span style="font-weight: 400; font-size: 0.75rem; padding: 0.7rem"
            >or login with</span
          >
          <img
            :src="googleLogo"
            alt="googleLogo"
            @click="googleSignIn"
            style="cursor: pointer"
          />
        </div>
        <div
          v-if="regIsVisible"
          style="display: flex; flex-direction: column; align-items: center"
        >
          <img
            :src="lineupLogo"
            alt="lineupLogo"
            class="logo"
            style="margin-top: 1.5rem"
          />
          <div>
            <button
              class="logRegSwitch"
              :class="{ active: isLogin }"
              @click="showLogin"
            >
              Login
            </button>
            <button
              class="logRegSwitch"
              :class="{ active: !isLogin }"
              @click="showRegister"
            >
              Register
            </button>
          </div>
          <form @submit.prevent="handleRegister">
            <input type="email" placeholder="Email" v-model="registerEmail" />
            <input
              type="password"
              placeholder="Password"
              v-model="registerPassword"
            />
            <input
              type="password"
              placeholder="Confirm Password"
              v-model="registerConfPassword"
            />
            <button type="submit">Register</button>
          </form>
          <span style="font-weight: 400; font-size: 0.75rem; padding: 0.7rem"
            >or login with</span
          >
          <img
            :src="googleLogo"
            alt="googleLogo"
            @click="googleSignIn"
            style="cursor: pointer"
          />
        </div>
        <div v-if="authIsVisible">
          <div
            style="display: flex; flex-direction: column; align-items: center"
          >
            <img
              :src="lineupLogo"
              alt="lineupLogo"
              class="logo"
              style="margin-top: 1.5rem"
            />
            <p>Enter the 6-digit code sent to your email.</p>
            <div class="numContainer">
              <div class="numbox" v-for="(digit, index) in code" :key="index">
                <form>
                  <input
                    type="text"
                    required
                    class="num"
                    maxlength="1"
                    inputmode="numeric"
                    @input="validateInput($event)"
                    v-model="code[index]"
                  />
                </form>
              </div>
            </div>
            <button class="verifyButton" @click="authenticate">Verify</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import lineupLogo from "@/assets/darkLogo.svg";
  import googleLogo from "@/assets/googleLogo.svg";
  import { supabase } from "../client/supabase";

  export default {
    name: "loginBox",
    data() {
      return {
        lineupLogo,
        googleLogo,
        isLogin: true,
        regIsVisible: false,
        loginEmail: "",
        loginPassword: "",
        registerEmail: "",
        registerPassword: "",
        registerConfPassword: "",
        authIsVisible: false,
        code: Array(6).fill(""),
      };
    },
    async mounted() {
      const email = await this.getEmail();
      if (email) {
        this.homeDirectory(email);
      } else {
        this.$router.push("login");
      }
    },
    methods: {
      async homeDirectory(email) {
        const { data, error } = await supabase
          .from("users")
          .select("role")
          .eq("email", email);

        if (data.length === 0) {
          this.$router.push("/");
        } else {
          if (data[0].role === "staff") {
            this.$router.push("stafflogin");
          } else if (data[0].role === "system admin") {
            this.$router.push("sysadhome");
          } else if (data[0].role ==="super admin") {
            this.$router.push("superHome");
          }
        }
        if (error) {
          console.error(error);
        }
      },
      async getEmail() {
        const {
          data: { session },
          error,
        } = await supabase.auth.getSession();

        if (session) {
          return session.user.email;
        }
      },
      showLogin() {
        this.isLogin = true;
        this.regIsVisible = false;
      },
      showRegister() {
        this.isLogin = false;
        this.regIsVisible = true;
      },
      async handleLogin() {
        const { data, error } = await supabase.auth.signInWithPassword({
          email: this.loginEmail,
          password: this.loginPassword,
        });
        if (error) {
          alert("Invalid username or password.");
          console.error(error);
        } else {
          this.loginIsVisible = !this.loginIsVisible;
          this.homeDirectory(this.loginEmail);
        }
      },
      async handleRegister() {
        if (this.registerPassword === this.registerConfPassword) {
          const { data, error } = await supabase.auth.signUp({
            email: this.registerEmail,
            password: this.registerPassword,
          });

          if (error) {
            alert(`${error.message}.`);
          } else {
            const { data, error } = await supabase.auth.signInWithOtp({
              email: this.registerEmail,
              options: {
                shouldCreateUser: true
              }
            })
            this.authIsVisible = !this.authIsVisible;
            this.regIsVisible = false;
          }
        } else {
          alert("Password didn't match! Please try again.");
        }
      },
      async googleSignIn() {
        const { data, error } = await supabase.auth.signInWithOAuth({
          provider: "google",
          options: {
            redirectTo: `${window.location.origin}/direct`,
          },
        });
        if (error) {
          console.log(error);
        }
      },
      validateInput(event) {
        const input = event.target;
        if (!/^\d*$/.test(input.value)) {
          input.value = "";
        }
      },
      async authenticate() {
        const {
          data: { session },
          error,
        } = await supabase.auth.verifyOtp({
          email: this.registerEmail,
          token: this.code.join(""),
          type: "email",
        });
        if (error) {
          console.log(error);
          alert("Invalid OTP! Check and enter again.");
        } else {
          console.log(session);
          this.$router.push("direct");
        }
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
    height: 33rem;
    padding: 2rem;
    background-color: white;
    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
    border-radius: 10px;
  }

  .logRegSwitch {
    width: 11.25rem;
    height: 2.1875rem;
    background-color: white;
    border: 1px solid #052c65;
    border-radius: 3px;
    margin: -1px;
    margin-top: 0.5rem;
    margin-bottom: 0.5rem;
    cursor: pointer;
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
    padding: 0.5rem;
    border: 1px solid #ccc;
    border-radius: 4px;
  }

  button[type="submit"] {
    background-color: #052c65;
    width: 10rem;
    color: white;
    border: none;
    padding: 0.5rem;
    border-radius: 4px;
    cursor: pointer;
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
</style>
