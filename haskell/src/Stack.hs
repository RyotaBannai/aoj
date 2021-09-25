{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module Stack where

import Common (sub')

-- * ALDS1_3_A

type Stack = [Integer]

type Expr = [String]

opts :: [String]
opts = ["+", "*", "-"]

expr :: (Expr, Stack) -> Stack
expr ([], s) = s
expr (x : xs, s) = if x `elem` opts then expr (xs, eval x s) else expr (xs, read x : s)

eval :: String -> Stack -> Stack
eval ops (x : y : s) = case ops of
  "+" -> y + x : s
  "*" -> y * x : s
  "-" -> sub' x y : s
  _ -> x : y : s

main :: IO ()
main = getLine >>= print . head . expr . (\s -> (words s, []))